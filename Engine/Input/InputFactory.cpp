#include "InputFactory.h"
#include "DirectInput/Input_DirectInput8.h"

InputFactory* InputFactory::g_InputFactory = nullptr;

// 构造
InputFactory::InputFactory() {
	InputType = InputType_DirectInput8;
	g_Input = nullptr;

	// DirectInput8 用参数
	g_hinstance = nullptr;
	g_hWnd = nullptr;
}

// 析构
InputFactory::~InputFactory() {

}


// 初始化控制器
// InputType_DirectInput8: 线程句柄，窗口句柄
void InputFactory::InitInput(int InputType, ...) {
	auto factory_input = InputFactory::GetInstance();
	if (factory_input) {
		// 设置控制器类型
		factory_input->InputType = InputType;

		// 定义参数列表
		va_list ap;

		// 初始化参数列表
		va_start(ap, InputType);


		switch (InputType) {
		case InputType_DirectInput8:
		{
			// 获取基础参数
			HINSTANCE hinstance = va_arg(ap, HINSTANCE);
			HWND hWnd = va_arg(ap, HWND);

			// 设置控制器参数
			factory_input->g_hinstance = hinstance;
			factory_input->g_hWnd = hWnd;

			// 初始化
			factory_input->InitInput_DirectInput8();
		}
		break;
		default:
			break;
		}

		// 结束参数设置
		va_end(ap);
	}
}

// 获取控制器工厂
InputFactory* InputFactory::GetInstance() {
	if (!g_InputFactory) {
		g_InputFactory = new InputFactory();
	}
	return g_InputFactory;
}

// 释放
void InputFactory::Release() {

}

// 获取控制器
Input* InputFactory::GetInput() {
	return g_Input;
}


// 初始化DirectInput8类型控制器
void InputFactory::InitInput_DirectInput8() {
	if (!g_Input) {
		g_Input = new Input_DirectInput8();
		if (g_Input) {
			auto ret = g_Input->BuildInput(g_hinstance, g_hWnd);
			if (ret) {

			}
		}
	}
}