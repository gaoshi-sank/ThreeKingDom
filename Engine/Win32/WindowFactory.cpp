#include "WindowFactory.h"
#include "../Render/RenderFactory.h"
#include "../Umg/UIFactory.h"

// ����
Window::Window() {
    m_hWnd = nullptr;
    m_fatherhWnd = nullptr;
    m_hinstance = nullptr;
    m_menu = nullptr;
    x = y = width = height = 0;
    style = WS_POPUP | WS_VISIBLE;
    isfull = true;

    wsprintf(szTitle, "Engine2D");
    wsprintf(szWindowClass, "Engine2D_%p", this);
}

// ����
Window::~Window() {

}

// ����
void Window::Create() {
    // ���ִ������
    if (m_hinstance && !m_fatherhWnd) {
        WNDCLASS wcex = { 0 };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.lpfnWndProc = WndProc;                         // ���� ���ڻص�
        wcex.hInstance = m_hinstance;                       // ���� ģ��ʵ�����
        wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);    // ���� Ĭ��ͼ��
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);      // ���� Ĭ�Ϲ��
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    // ���� ������ɫ
        wcex.lpszMenuName = "";                             // ���� ������
        wcex.lpszClassName = szWindowClass;                 // ���� ����

        if (!RegisterClass(&wcex)) {
            return;
        }
    }

    // ��������
    m_hWnd = CreateWindow(
        szWindowClass,  // ����
        szTitle,        // ��������
        style,          // ���ڵĴ�����ʽ
        x,
        y,
        width,
        height,
        m_fatherhWnd,   // ������
        m_menu,         // �˵���
        m_hinstance,    // ʵ�����
        (LPVOID)this);  // ���ⴴ������

    if (!m_hWnd) {
        return;
    }
}

// ��Ϣ���� - ��ѭ��
void Window::Process() {
    // ��ʾ�͸���
    ShowWindow(m_hWnd, isfull ? SW_MAXIMIZE : SW_SHOW);
    UpdateWindow(m_hWnd);

    // ѭ����Ϣ
    MSG msg = { 0 };
    while (1) {
        // ��������win32��Ϣ
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                break;
            }
        }
        // ����ʱ��
        else {
            
        }
    }

}

// ��ȡ���
HWND Window::GetHandle() {
    return this->m_hWnd;
}

// ���ڻص�����
LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    auto param = new unsigned int[4];
    memset(param, 0, sizeof(unsigned int) * 4);
    param[1] = message;

    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOUSEMOVE:
        param[0] = 3;
        param[2] = (unsigned int)lParam;
        UIFactory::CheckEvent(param);
        break;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
        param[0] = 2;
        UIFactory::CheckEvent(param);
        break;
    default:
        break;
    }

    delete[] param;
    param = nullptr;

    return DefWindowProc(hwnd, message, wParam, lParam);
}

// ����
bool WindowFactory::isMainBuild = false;
HINSTANCE WindowFactory::hinstance = nullptr;

// ���þ��
void WindowFactory::SethInstance(HINSTANCE _hinstance) {
    hinstance = _hinstance;
}

// �½�һ������
// Ĭ��ȫ��
std::shared_ptr<Window> WindowFactory::Build() {
    std::shared_ptr<Window> result = nullptr;
    if (!isMainBuild) {
        isMainBuild = true;

        // Ĭ������
        auto width = GetSystemMetrics(SM_CXSCREEN);
        auto height = GetSystemMetrics(SM_CYSCREEN);
        auto style = WS_POPUP | WS_VISIBLE;

        // ����
        result = std::make_shared<Window>();
        if (result) {
            result->width = width;
            result->height = height;
            result->style = style;
            result->m_hinstance = hinstance;

            // ����
            result->Create();
        }
    }
    return result;
}

// �½�һ������
// ���� - λ�úʹ�С
std::shared_ptr<Window> WindowFactory::Build(int x, int y, int width, int height) {
    std::shared_ptr<Window> result = nullptr;
    if (!isMainBuild) {
        isMainBuild = true;

        // ����
        result = std::make_shared<Window>();
        if (result) {
            result->x = x;
            result->y = y;
            result->width = width;
            result->height = height;
            result->style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
            result->isfull = false;
            result->m_hinstance = hinstance;

            // ����
            result->Create();
        }
    }
    return result;
}