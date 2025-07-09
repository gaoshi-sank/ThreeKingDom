#ifndef _WindowFactory_h_
#define _WindowFactory_h_

// 包含库
#include <Windows.h>
#include "../EngineConfig.h"

// 类前置声明
class Window;
class WindowFactory;

// 窗口封装Win32类
// 目前问题：不能同时多个窗口
class Window {
private:
	HWND m_hWnd;				// 当前窗口句柄
	HWND m_fatherhWnd;			// 父窗口句柄
	HINSTANCE m_hinstance;		// 实例句柄
	HMENU m_menu;				// 菜单句柄（子窗口ID）
	int style;					// 窗口风格
	int x, y, width, height;	// 窗口区域
	bool isfull;				// 全屏状态
	char szTitle[32];			// 标题
	char szWindowClass[32];		// 类名

	friend class WindowFactory; // 友元类

	// 主线程回调用函数
	std::function<void()> msgCallback;

public:
	// 构造
	Window();

	// 析构
	~Window();

	// 消息控制
	virtual void Process();

	// 获取句柄
	virtual HWND GetHandle();

private:
	// 创建
	void Create(std::function<void()> _callback);

	// 窗口回调函数
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

// 窗口 - 工厂
class WindowFactory {
private:
	// 构造
	WindowFactory() = default;

	// 析构
	~WindowFactory() = default;

	// 属性
	static bool isMainBuild;
	static HINSTANCE hinstance;

public:
	// 删除 复制构造函数 和 赋值重载函数
	WindowFactory(const WindowFactory&) = delete;
	WindowFactory& operator=(const WindowFactory&) = delete;

	// 设置句柄
	static void SethInstance(HINSTANCE _hinstance);

	// 新建一个窗口
	// 默认全屏
	static std::shared_ptr<Window> Build(std::function<void()> _callback = nullptr);

	// 新建一个窗口
	// 参数 - 位置和大小
	static std::shared_ptr<Window> Build(int x, int y, int width, int height, std::function<void()> _callback = nullptr);
};


#endif //!_WindowFactory_h_