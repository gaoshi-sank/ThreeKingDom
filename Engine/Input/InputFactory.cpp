#include "InputFactory.h"
#include "DirectInput/Input_DirectInput8.h"

InputFactory* InputFactory::g_InputFactory = nullptr;

// ����
InputFactory::InputFactory() {
	InputType = InputType_DirectInput8;
	g_Input = nullptr;

	// DirectInput8 �ò���
	g_hinstance = nullptr;
	g_hWnd = nullptr;
}

// ����
InputFactory::~InputFactory() {

}


// ��ʼ��������
// InputType_DirectInput8: �߳̾�������ھ��
void InputFactory::InitInput(int InputType, ...) {
	auto factory_input = InputFactory::GetInstance();
	if (factory_input) {
		// ���ÿ���������
		factory_input->InputType = InputType;

		// ��������б�
		va_list ap;

		// ��ʼ�������б�
		va_start(ap, InputType);


		switch (InputType) {
		case InputType_DirectInput8:
		{
			// ��ȡ��������
			HINSTANCE hinstance = va_arg(ap, HINSTANCE);
			HWND hWnd = va_arg(ap, HWND);

			// ���ÿ���������
			factory_input->g_hinstance = hinstance;
			factory_input->g_hWnd = hWnd;

			// ��ʼ��
			factory_input->InitInput_DirectInput8();
		}
		break;
		default:
			break;
		}

		// ������������
		va_end(ap);
	}
}

// ��ȡ����������
InputFactory* InputFactory::GetInstance() {
	if (!g_InputFactory) {
		g_InputFactory = new InputFactory();
	}
	return g_InputFactory;
}

// �ͷ�
void InputFactory::Release() {

}

// ��ȡ������
Input* InputFactory::GetInput() {
	return g_Input;
}


// ��ʼ��DirectInput8���Ϳ�����
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