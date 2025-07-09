#include "EngineProvider.h"

int EngineProvider::buildEngine_state = 0;			// 引擎构建状态
EngineProvider* EngineProvider::g_eng = nullptr;

// 构造
EngineProvider::EngineProvider() {
	// 属性
	engine_hInstance = nullptr; // 进程句柄
	render_Thread = nullptr;	// 渲染用线程
	renderState = 0;			// 渲染 - 状态

	// 配置
	setting_fps = 0;
	setting_windowX = 0;
	setting_windowY = 0;
	setting_windowWidth = 0;
	setting_windowHeight = 0;
}

// 析构
EngineProvider::~EngineProvider() {

}

// 获取引擎
EngineProvider* EngineProvider::GetInstance() {
	return g_eng;
}

// 初始化引擎
void EngineProvider::InitEngine(HINSTANCE _hinst, bool isFull, int width, int height) {
	if (!g_eng) {
		g_eng = new EngineProvider();
	}
	
	auto x = 0;
	auto y = 0;
	auto win32_width = GetSystemMetrics(SM_CXSCREEN);
	auto win32_height = GetSystemMetrics(SM_CYSCREEN);
	if (!isFull) {
		x = (win32_width - width) / 2;
		y = (win32_height - height) / 2;
		win32_width = width;
		win32_height = height;
	}

	g_eng->engine_hInstance = _hinst;
	g_eng->BuildEngineStruct(x, y, win32_width, win32_height, isFull);
}

// 运行引擎
void EngineProvider::RunEngine() {
	if (g_eng) {
		g_eng->MainRunLoop();
	}
}

// 获取程序窗口大小
void EngineProvider::GetWindowSize(int& x, int& y, int& width, int& height) {
	x = setting_windowX;
	y = setting_windowY;
	width = setting_windowWidth;
	height = setting_windowHeight;
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
	setting_windowX = x;
	setting_windowY = y;
	setting_windowWidth = width;
	setting_windowHeight = height;
	WindowFactory::SethInstance(engine_hInstance);
	if (isFull) {
		this->mainWindow = WindowFactory::Build([&]() {
			CallbackUpdate();
		});
	}
	else {
		this->mainWindow = WindowFactory::Build(x, y, width, height, [&]() {
			CallbackUpdate();
		});
	}


	// 构建控制系统
	InputFactory::InitInput(InputFactory::InputType_DirectInput8, engine_hInstance, mainWindow->GetHandle());

	// 构建渲染系统
	RenderFactory::InitRender(mainWindow->GetHandle(), width, height);

	// 构建UI系统
	UIFactory::InitUIProvider();

	// 构建场景系统
	SceneManager::InitSceneManager();


	// 构建独立线程
	renderState = 1;
	render_Thread = new std::thread(&EngineProvider::RenderLoop, this);

	// 修改引擎构建状态
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

// Win32线程回调更新处理
void EngineProvider::CallbackUpdate() {

	// 计时器
	if (update_timer == nullptr) {
		update_timer = std::make_shared<Timer>();
		update_timer->start();
	}

	// 更新
	// 基础计时
	update_timer->getStart();

	{
		// UI系统 更新
		UIFactory::Update();

		// Scene系统
		SceneManager::UpdateScene();
	}

	// 结束计时
	auto _time = update_timer->getOvertime();
	auto fps_time = GetConfig_Fps();
	if (fps_time > _time) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(fps_time - _time)));
	}
}

// 独立线程渲染
void EngineProvider::RenderLoop() {
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

}

// 等待线程结束
void EngineProvider::WaittingThreadProcess() {
	// 等待线程结束
	renderState = 0;
	if (render_Thread) {
		render_Thread->join();
		delete render_Thread;
		render_Thread = nullptr;
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