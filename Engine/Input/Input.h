#ifndef _Input_h_
#define _Input_h_

#include <Windows.h>
#include <Windowsx.h>
#include "../EngineConfig.h"


// 抽象控制器
class Input {
public:
	// 默认构造和析构
	Input() = default;
	virtual ~Input() = default;

	// 建立控制器
	virtual bool BuildInput(HINSTANCE hinstance, HWND hWnd) = 0;

	// 释放控制器
	virtual void Release() = 0;

	// 获取键盘状态
	virtual bool GetKeyState(int key) = 0;

	// 获取鼠标状态
	// 0 - 鼠标左键，1 - 鼠标右键
	virtual bool GetMouseState(int key) = 0;
};



#endif // !_Input_h_
