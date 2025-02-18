#ifndef _EngineProvider_h_
#define _EngineProvider_h_

#include "EngineConfig.h"
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"
#include "Input/InputFactory.h"
#include "Timer/TimerFactory.h"
#include "Umg/UIFactory.h"
#include "Scene/SceneManager.h"
#include "Render/Sprite/SSprite.h"
#include "FIleControl/FileControl.h"
#include "Log/LogSystem.h"
#include "Collision/Collision.h"

// ���������
class EngineProvider {
private:
	// ����
	EngineProvider();

	// ����
	~EngineProvider();

	// ��ֵ̬
	static int buildEngine_state;
	static EngineProvider* g_eng;

	// ����
	HINSTANCE engine_hInstance;			// ���̾��
	std::shared_ptr<Window> mainWindow;	// ������
	std::thread* update_Thread;			// �������߳�
	std::thread* render_Thread;			// ��Ⱦ���߳�
	int updateState;					// ���� - ״̬
	int renderState;					// ��Ⱦ - ״̬
	std::mutex lock_update;				// �� - ����
	std::mutex lock_render;				// �� - ��Ⱦ
	std::condition_variable cv_update;	// ���� - ����
	std::condition_variable cv_render;	// ���� - ��Ⱦ

	// ����
	double setting_fps;		// ֡��
	int setting_render;		// ��Ⱦ����

public:
	// ��ȡ����
	static EngineProvider* GetInstance();

	// ��ʼ������
	static void InitEngine(HINSTANCE _hinst = nullptr, int renderType = RenderFactory::RenderType_Direct2D, bool isFull = true, int width = 0, int height = 0);

	// ��������
	static void RunEngine();

private:
	// ��������
	void BuildEngineStruct(int x, int y, int width, int height, bool isFull = false);

	// ���߳�����
	void MainRunLoop();

	// �������߳�
	void ThreadLoop_RunUpdate();

	// ��Ⱦ���߳�
	void ThreadLoop_RunRender();

	// �ȴ��߳̽���
	void WaittingThreadProcess();

private:
	// ��ȡ�����ļ�
	void ReadConfig();

	// ��ȡ���� - ֡��
	double GetConfig_Fps() const;

};

#endif // !_EngineProvider_h_
