#ifndef _WindowFactory_h_
#define _WindowFactory_h_

// ������
#include <Windows.h>
#include "../EngineConfig.h"

// ��ǰ������
class Window;
class WindowFactory;

// ���ڷ�װWin32��
// Ŀǰ���⣺����ͬʱ�������
class Window {
private:
	HWND m_hWnd;				// ��ǰ���ھ��
	HWND m_fatherhWnd;			// �����ھ��
	HINSTANCE m_hinstance;		// ʵ�����
	HMENU m_menu;				// �˵�������Ӵ���ID��
	int style;					// ���ڷ��
	int x, y, width, height;	// ��������
	bool isfull;				// ȫ��״̬
	char szTitle[32];			// ����
	char szWindowClass[32];		// ����

	friend class WindowFactory;


public:
	// ����
	Window();

	// ����
	~Window();

	// ��Ϣ����
	virtual void Process();

	// ��ȡ���
	virtual HWND GetHandle();

private:
	// ����
	void Create();

	// ���ڻص�����
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

// ���� - ����
class WindowFactory {
private:
	// ����
	WindowFactory() = default;

	// ����
	~WindowFactory() = default;

	// ����
	static bool isMainBuild;
	static HINSTANCE hinstance;

public:
	// ɾ�� ���ƹ��캯�� �� ��ֵ���غ���
	WindowFactory(const WindowFactory&) = delete;
	WindowFactory& operator=(const WindowFactory&) = delete;

	// ���þ��
	static void SethInstance(HINSTANCE _hinstance);

	// �½�һ������
	// Ĭ��ȫ��
	static std::shared_ptr<Window> Build();

	// �½�һ������
	// ���� - λ�úʹ�С
	static std::shared_ptr<Window> Build(int x, int y, int width, int height);
};


#endif //!_WindowFactory_h_