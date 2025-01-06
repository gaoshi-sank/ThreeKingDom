#ifndef _InputFactory_h_
#define _InputFactory_h_


#include "Input.h"


// ����������
class InputFactory {
public:
	// ����������
	enum InputType {
		InputType_DirectInput8 = 1,	// DirectInput8
	};

private:
	// ����
	InputFactory();

	// ����
	~InputFactory();

	// ����
	int InputType;
	Input* g_Input;

	// DirectInput8 �ò���
	HINSTANCE g_hinstance;
	HWND g_hWnd;

	// ��ֵ̬
	static InputFactory* g_InputFactory;

public:
	// ��ʼ��������
	// InputType_DirectInput8: �߳̾�������ھ��
	static void InitInput(int InputType, ...);

	// ��ȡ����������
	static InputFactory* GetInstance();

	// �ͷ�
	static void Release();

	// ��ȡ������
	Input* GetInput();

private:
	// ��ʼ��DirectInput8���Ϳ�����
	void InitInput_DirectInput8();

};



#endif // !_InputFactory_h_