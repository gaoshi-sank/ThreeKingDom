#include "EngineProvider.h"

int EngineProvider::buildEngine_state = 0;
EngineProvider* EngineProvider::g_eng = nullptr;

// 构造
EngineProvider::EngineProvider() {
	// 属性
	engine_hInstance = nullptr; // 进程句柄
	update_Thread = nullptr;	// 更新用线程
	render_Thread = nullptr;	// 渲染用线程
	updateState = 0;			// 更新 - 状态
	renderState = 0;			// 渲染 - 状态

	// 配置
	setting_fps = 0;
}

// 析构
EngineProvider::~EngineProvider() {

}

// 获取引擎
EngineProvider* EngineProvider::GetInstance() {
	return g_eng;
}

// 初始化引擎
void EngineProvider::InitEngine(HINSTANCE _hinst, int renderType, bool isFull, int width, int height) {
	if (!g_eng) {
		g_eng = new EngineProvider();
	}
	
	auto x = 0;
	auto y = 0;
	auto win32_width = 0;
	auto win32_height = 0;
	if (isFull) {
		win32_width = GetSystemMetrics(SM_CXSCREEN);
		win32_height = GetSystemMetrics(SM_CYSCREEN);
	}
	else {
		x = (win32_width - width) / 2;
		y = (win32_height - height) / 2;
	}

	g_eng->engine_hInstance = _hinst;
	g_eng->setting_render = renderType;
	g_eng->BuildEngineStruct(x, y, win32_width, win32_height, isFull);
}

// 运行引擎
void EngineProvider::RunEngine() {
	if (g_eng) {
		g_eng->MainRunLoop();
	}
}

// 构建引擎
void EngineProvider::BuildEngineStruct(int x, int y, int width, int height, bool isFull) {
	if (buildEngine_state == 1) {
		return;
	}

	// 构建文件处理系统
	FileControl::InitFileControl();

	// 开始构建
	// 构建计时器系统
	TimerFactory::InitTimerFactory();

	// 构建Win32系统
	WindowFactory::SethInstance(engine_hInstance);
	if (isFull) {
		this->mainWindow = WindowFactory::Build();
	}
	else {
		this->mainWindow = WindowFactory::Build(x, y, width, height);
	}


	// 构建控制系统
	InputFactory::InitInput(InputFactory::InputType_DirectInput8, engine_hInstance, mainWindow->GetHandle());

	// 构建渲染系统
	RenderFactory::InitRender(setting_render, mainWindow->GetHandle(), width, height);

	// 构建UI系统
	UIFactory::InitUIProvider();

	// 构建场景系统
	SceneManager::InitSceneManager();


	// 构建独立线程
	updateState = 1;
	renderState = 1;
	update_Thread = new std::thread(&EngineProvider::ThreadLoop_RunUpdate, this);
	render_Thread = new std::thread(&EngineProvider::ThreadLoop_RunRender, this);

	buildEngine_state = 1;
}

// 主线程运行
void EngineProvider::MainRunLoop() {
	// win32窗口消息
	if (mainWindow) {
		mainWindow->Process();
	}

	// 等待线程结束
	WaittingThreadProcess();

	// 其他模块处理
	UIFactory::Release();			// UI模块
	RenderFactory::Release();		// 渲染器模块
	TimerFactory::Release();		// 计时器模块
	SceneManager::ReleaseScene();	// 场景模块
}

// 更新用线程
void EngineProvider::ThreadLoop_RunUpdate() {
	// 计时器
	std::shared_ptr<Timer> update_timer = std::make_shared<Timer>();
	update_timer->start();

	// 更新循环
	while (updateState) {
		// 基础计时
		update_timer->getStart();

		// UI系统 更新
		UIFactory::Update();

		// Scene系统
		SceneManager::UpdateScene();

		// 结束计时
		auto _time = update_timer->getOvertime();
		auto fps_time = GetConfig_Fps();
		if (fps_time > _time) {
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(fps_time - _time)));
		}
	}

	// 修改状态值
	{
		std::unique_lock<std::mutex> lock(lock_update);
		updateState = 2;
		cv_update.notify_one();
	}

}

// 渲染用线程
void EngineProvider::ThreadLoop_RunRender() {
	// 计时器
	std::shared_ptr<Timer> render_timer = std::make_shared<Timer>();
	render_timer->start();

	// 更新渲染
	while (renderState) {
		// 基础计时
		render_timer->getStart();

		// 渲染
		auto renderFactory = RenderFactory::GetInstance();
		if (renderFactory) {
			auto render = renderFactory->GetRender();
			if (render) {
				// 开始渲染
				render->BeginPlay();

				// UI系统 渲染
				UIFactory::Draw();

				// Scene系统
				SceneManager::DrawScene();

				// 结束渲染
				render->EndPlay();
			}
		}

		// 结束计时
		auto _time = render_timer->getOvertime();
		auto fps_time = GetConfig_Fps();
		if (fps_time > _time) {
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(fps_time - _time)));
		}
	}

	// 修改状态值
	{
		std::unique_lock<std::mutex> lock(lock_render);
		renderState = 2;
		cv_render.notify_one();
	}
}

// 等待线程结束
void EngineProvider::WaittingThreadProcess() {
	// 等待线程结束

	// 更新线程
	{
		updateState = 0;
		std::unique_lock<std::mutex> lock(lock_update);
		cv_update.wait(lock, [&]() {
			return updateState == 2;
		});
	}

	// 渲染线程
	{
		renderState = 0;
		std::unique_lock<std::mutex> lock(lock_render);
		cv_render.wait(lock, [&]() {
			return renderState == 2;
		});
	}
}

// 读取配置文件
void EngineProvider::ReadConfig() {
	// 构建初始值
	setting_fps = 1000.0 / 60;	// 60fps

}

// 获取配置 - 帧率
double EngineProvider::GetConfig_Fps() const {
	return setting_fps;
}