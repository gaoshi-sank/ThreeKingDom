#ifndef _Input_h_
#define _Input_h_

#include <Windows.h>
#include <Windowsx.h>
#include "../EngineConfig.h"


// ���������
class Input {
public:
	// Ĭ�Ϲ��������
	Input() = default;
	virtual ~Input() = default;

	// ����������
	virtual bool BuildInput(HINSTANCE hinstance, HWND hWnd) = 0;

	// �ͷſ�����
	virtual void Release() = 0;

	// ��ȡ����״̬
	virtual bool GetKeyState(int key) = 0;

	// ��ȡ���״̬
	// 0 - ��������1 - ����Ҽ�
	virtual bool GetMouseState(int key) = 0;
};



#endif // !_Input_h_
