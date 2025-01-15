#ifndef _Input_DirectInput8_h_
#define _Input_DirectInput8_h_

#include "../Input.h"

// �����������ļ�
#include <dinput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

// ���������
class Input_DirectInput8 : public Input{
private:
	LPDIRECTINPUT8 g_DirectInput;
	LPDIRECTINPUTDEVICE8 g_keyboard;
	LPDIRECTINPUTDEVICE8 g_mouseboard;
	HWND g_hWnd;

public:
	// ����
	Input_DirectInput8();

	// ����
	~Input_DirectInput8();

	// ����������
	virtual bool BuildInput(HINSTANCE hinstance, HWND hWnd);

	// �ͷſ�����
	virtual void Release();

	// ��ȡ����״̬
	virtual bool GetKeyState(int key);

	// ��ȡ���״̬
	// 0 - ��������1 - ����Ҽ�
	virtual bool GetMouseState(int key);

	// ��ȡ���λ��
	virtual bool GetMousePos(int& x, int& y);
};

#endif // !_Input_DirectInput8_h_
