#ifndef _EngineProvider_h_
#define _EngineProvider_h_

#include "EngineHelper.h"
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
	std::shared_ptr<Timer> update_timer;// win32�ص���ʱ��
	std::thread* render_Thread;			// ��Ⱦ���߳�
	int renderState;					// ��Ⱦ - ״̬

	// ����
	double setting_fps;					// ֡��
	int setting_windowX;				// ��������
	int setting_windowY;				// 
	int setting_windowWidth;			// 
	int setting_windowHeight;			// 

public:
	// ��ȡ����
	static EngineProvider* GetInstance();

	// ��ʼ������
	static void InitEngine(HINSTANCE _hinst = nullptr, bool isFull = true, int width = 0, int height = 0);

	// ��������
	static void RunEngine();

	// ��ȡ���򴰿ڴ�С
	void GetWindowSize(int& x, int& y, int& width, int& height);

private:
	// ��������
	void BuildEngineStruct(int x, int y, int width, int height, bool isFull = false);

	// ���߳�����
	void MainRunLoop();

	// Win32�̻߳ص����´���
	void CallbackUpdate();

	// �����߳���Ⱦ
	void RenderLoop();

	// �ȴ��߳̽���
	void WaittingThreadProcess();

private:
	// ��ȡ�����ļ�
	void ReadConfig();

	// ��ȡ���� - ֡��
	double GetConfig_Fps() const;

};

#endif // !_EngineProvider_h_
