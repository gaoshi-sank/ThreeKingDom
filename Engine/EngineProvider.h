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

// 引擎管理类
class EngineProvider {
private:
	// 构造
	EngineProvider();

	// 析构
	~EngineProvider();

	// 静态值
	static int buildEngine_state;
	static EngineProvider* g_eng;

	// 属性
	HINSTANCE engine_hInstance;			// 进程句柄
	std::shared_ptr<Window> mainWindow;	// 主窗口
	std::shared_ptr<Timer> update_timer;// win32回调计时器
	std::thread* render_Thread;			// 渲染用线程
	int renderState;					// 渲染 - 状态

	// 配置
	double setting_fps;					// 帧率
	int setting_windowX;				// 窗口区域
	int setting_windowY;				// 
	int setting_windowWidth;			// 
	int setting_windowHeight;			// 

public:
	// 获取引擎
	static EngineProvider* GetInstance();

	// 初始化引擎
	static void InitEngine(HINSTANCE _hinst = nullptr, bool isFull = true, int width = 0, int height = 0);

	// 运行引擎
	static void RunEngine();

	// 获取程序窗口大小
	void GetWindowSize(int& x, int& y, int& width, int& height);

private:
	// 构建引擎
	void BuildEngineStruct(int x, int y, int width, int height, bool isFull = false);

	// 主线程运行
	void MainRunLoop();

	// Win32线程回调更新处理
	void CallbackUpdate();

	// 独立线程渲染
	void RenderLoop();

	// 等待线程结束
	void WaittingThreadProcess();

private:
	// 读取配置文件
	void ReadConfig();

	// 获取配置 - 帧率
	double GetConfig_Fps() const;

};

#endif // !_EngineProvider_h_
