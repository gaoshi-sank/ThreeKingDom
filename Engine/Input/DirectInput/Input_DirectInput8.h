#ifndef _Input_DirectInput8_h_
#define _Input_DirectInput8_h_

#include "../Input.h"

// 控制器包含文件
#include <dinput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

// 抽象控制器
class Input_DirectInput8 : public Input{
private:
	LPDIRECTINPUT8 g_DirectInput;
	LPDIRECTINPUTDEVICE8 g_keyboard;
	LPDIRECTINPUTDEVICE8 g_mouseboard;
	HWND g_hWnd;

public:
	// 构造
	Input_DirectInput8();

	// 析构
	~Input_DirectInput8();

	// 建立控制器
	virtual bool BuildInput(HINSTANCE hinstance, HWND hWnd);

	// 释放控制器
	virtual void Release();

	// 获取键盘状态
	virtual bool GetKeyState(int key);

	// 获取鼠标状态
	// 0 - 鼠标左键，1 - 鼠标右键
	virtual bool GetMouseState(int key);

	// 获取光标位置
	virtual bool GetMousePos(int& x, int& y);
};

#endif // !_Input_DirectInput8_h_
