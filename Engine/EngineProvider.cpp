#include "EngineProvider.h"

int EngineProvider::buildEngine_state = 0;			// ���湹��״̬
EngineProvider* EngineProvider::g_eng = nullptr;

// ����
EngineProvider::EngineProvider() {
	// ����
	engine_hInstance = nullptr; // ���̾��
	render_Thread = nullptr;	// ��Ⱦ���߳�
	renderState = 0;			// ��Ⱦ - ״̬

	// ����
	setting_fps = 0;
	setting_windowX = 0;
	setting_windowY = 0;
	setting_windowWidth = 0;
	setting_windowHeight = 0;
}

// ����
EngineProvider::~EngineProvider() {

}

// ��ȡ����
EngineProvider* EngineProvider::GetInstance() {
	return g_eng;
}

// ��ʼ������
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

// ��������
void EngineProvider::RunEngine() {
	if (g_eng) {
		g_eng->MainRunLoop();
	}
}

// ��ȡ���򴰿ڴ�С
void EngineProvider::GetWindowSize(int& x, int& y, int& width, int& height) {
	x = setting_windowX;
	y = setting_windowY;
	width = setting_windowWidth;
	height = setting_windowHeight;
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


	// ��������ϵͳ
	InputFactory::InitInput(InputFactory::InputType_DirectInput8, engine_hInstance, mainWindow->GetHandle());

	// ������Ⱦϵͳ
	RenderFactory::InitRender(mainWindow->GetHandle(), width, height);

	// ����UIϵͳ
	UIFactory::InitUIProvider();

	// ��������ϵͳ
	SceneManager::InitSceneManager();


	// ���������߳�
	renderState = 1;
	render_Thread = new std::thread(&EngineProvider::RenderLoop, this);

	// �޸����湹��״̬
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

// Win32�̻߳ص����´���
void EngineProvider::CallbackUpdate() {

	// ��ʱ��
	if (update_timer == nullptr) {
		update_timer = std::make_shared<Timer>();
		update_timer->start();
	}

	// ����
	// ������ʱ
	update_timer->getStart();

	{
		// UIϵͳ ����
		UIFactory::Update();

		// Sceneϵͳ
		SceneManager::UpdateScene();
	}

	// ������ʱ
	auto _time = update_timer->getOvertime();
	auto fps_time = GetConfig_Fps();
	if (fps_time > _time) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(fps_time - _time)));
	}
}

// �����߳���Ⱦ
void EngineProvider::RenderLoop() {
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

}

// �ȴ��߳̽���
void EngineProvider::WaittingThreadProcess() {
	// �ȴ��߳̽���
	renderState = 0;
	if (render_Thread) {
		render_Thread->join();
		delete render_Thread;
		render_Thread = nullptr;
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