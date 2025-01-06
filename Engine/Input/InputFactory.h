#ifndef _InputFactory_h_
#define _InputFactory_h_


#include "Input.h"


// 控制器工厂
class InputFactory {
public:
	// 控制器类型
	enum InputType {
		InputType_DirectInput8 = 1,	// DirectInput8
	};

private:
	// 构造
	InputFactory();

	// 析构
	~InputFactory();

	// 属性
	int InputType;
	Input* g_Input;

	// DirectInput8 用参数
	HINSTANCE g_hinstance;
	HWND g_hWnd;

	// 静态值
	static InputFactory* g_InputFactory;

public:
	// 初始化控制器
	// InputType_DirectInput8: 线程句柄，窗口句柄
	static void InitInput(int InputType, ...);

	// 获取控制器工厂
	static InputFactory* GetInstance();

	// 释放
	static void Release();

	// 获取控制器
	Input* GetInput();

private:
	// 初始化DirectInput8类型控制器
	void InitInput_DirectInput8();

};



#endif // !_InputFactory_h_