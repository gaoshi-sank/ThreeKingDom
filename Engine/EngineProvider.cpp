#include "EngineProvider.h"

int EngineProvider::buildEngine_state = 0;
EngineProvider* EngineProvider::g_eng = nullptr;

// ����
EngineProvider::EngineProvider() {
	// ����
	engine_hInstance = nullptr; // ���̾��
	update_Thread = nullptr;	// �������߳�
	render_Thread = nullptr;	// ��Ⱦ���߳�
	updateState = 0;			// ���� - ״̬
	renderState = 0;			// ��Ⱦ - ״̬

	// ����
	setting_fps = 0;
	setting_render = 0;
}

// ����
EngineProvider::~EngineProvider() {

}

// ��ȡ����
EngineProvider* EngineProvider::GetInstance() {
	return g_eng;
}

// ��ʼ������
void EngineProvider::InitEngine(HINSTANCE _hinst, int renderType, bool isFull, int width, int height) {
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
	g_eng->setting_render = renderType;
	g_eng->BuildEngineStruct(x, y, win32_width, win32_height, isFull);
}

// ��������
void EngineProvider::RunEngine() {
	if (g_eng) {
		g_eng->MainRunLoop();
	}
}

// ��������
void EngineProvider::BuildEngineStruct(int x, int y, int width, int height, bool isFull) {
	if (buildEngine_state == 1) {
		return;
	}

	// �����ļ�����ϵͳ
	FileControl::InitFileControl();

	// ��ʼ����
	// ������ʱ��ϵͳ
	TimerFactory::InitTimerFactory();

	// ����Win32ϵͳ
	WindowFactory::SethInstance(engine_hInstance);
	if (isFull) {
		this->mainWindow = WindowFactory::Build();
	}
	else {
		this->mainWindow = WindowFactory::Build(x, y, width, height);
	}


	// ��������ϵͳ
	InputFactory::InitInput(InputFactory::InputType_DirectInput8, engine_hInstance, mainWindow->GetHandle());

	// ������Ⱦϵͳ
	RenderFactory::InitRender(setting_render, mainWindow->GetHandle(), width, height);

	// ����UIϵͳ
	UIFactory::InitUIProvider();

	// ��������ϵͳ
	SceneManager::InitSceneManager();


	// ���������߳�
	updateState = 1;
	renderState = 1;
	update_Thread = new std::thread(&EngineProvider::ThreadLoop_RunUpdate, this);
	render_Thread = new std::thread(&EngineProvider::ThreadLoop_RunRender, this);

	buildEngine_state = 1;
}

// ���߳�����
void EngineProvider::MainRunLoop() {
	// win32������Ϣ
	if (mainWindow) {
		mainWindow->Process();
	}

	// �ȴ��߳̽���
	WaittingThreadProcess();

	// ����ģ�鴦��
	UIFactory::Release();			// UIģ��
	RenderFactory::Release();		// ��Ⱦ��ģ��
	TimerFactory::Release();		// ��ʱ��ģ��
	SceneManager::ReleaseScene();	// ����ģ��
}

// �������߳�
void EngineProvider::ThreadLoop_RunUpdate() {
	// ��ʱ��
	std::shared_ptr<Timer> update_timer = std::make_shared<Timer>();
	update_timer->start();

	// ����ѭ��
	while (updateState) {
		// ������ʱ
		update_timer->getStart();

		// UIϵͳ ����
		UIFactory::Update();

		// Sceneϵͳ
		SceneManager::UpdateScene();

		// ������ʱ
		auto _time = update_timer->getOvertime();
		auto fps_time = GetConfig_Fps();
		if (fps_time > _time) {
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(fps_time - _time)));
		}
	}

	// �޸�״ֵ̬
	{
		std::unique_lock<std::mutex> lock(lock_update);
		updateState = 2;
		cv_update.notify_one();
	}

}

// ��Ⱦ���߳�
void EngineProvider::ThreadLoop_RunRender() {
	// ��ʱ��
	std::shared_ptr<Timer> render_timer = std::make_shared<Timer>();
	render_timer->start();

	// ������Ⱦ
	while (renderState) {
		// ������ʱ
		render_timer->getStart();

		// ��Ⱦ
		auto renderFactory = RenderFactory::GetInstance();
		if (renderFactory) {
			auto render = renderFactory->GetRender();
			if (render) {
				// ��ʼ��Ⱦ
				render->BeginPlay();

				// UIϵͳ ��Ⱦ
				UIFactory::Draw();

				// Sceneϵͳ
				SceneManager::DrawScene();

				// ������Ⱦ
				render->EndPlay();
			}
		}

		// ������ʱ
		auto _time = render_timer->getOvertime();
		auto fps_time = GetConfig_Fps();
		if (fps_time > _time) {
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(fps_time - _time)));
		}
	}

	// �޸�״ֵ̬
	{
		std::unique_lock<std::mutex> lock(lock_render);
		renderState = 2;
		cv_render.notify_one();
	}
}

// �ȴ��߳̽���
void EngineProvider::WaittingThreadProcess() {
	// �ȴ��߳̽���

	// �����߳�
	{
		updateState = 0;
		std::unique_lock<std::mutex> lock(lock_update);
		cv_update.wait(lock, [&]() {
			return updateState == 2;
		});
	}

	// ��Ⱦ�߳�
	{
		renderState = 0;
		std::unique_lock<std::mutex> lock(lock_render);
		cv_render.wait(lock, [&]() {
			return renderState == 2;
		});
	}
}

// ��ȡ�����ļ�
void EngineProvider::ReadConfig() {
	// ������ʼֵ
	setting_fps = 1000.0 / 60;	// 60fps

}

// ��ȡ���� - ֡��
double EngineProvider::GetConfig_Fps() const {
	return setting_fps;
}