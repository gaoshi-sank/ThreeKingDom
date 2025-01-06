#include "WindowFactory.h"
#include "../Render/RenderFactory.h"
#include "../Umg/UIFactory.h"

// 构造
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

// 析构
Window::~Window() {

}

// 创建
void Window::Create() {
    // 区分窗口类别
    if (m_hinstance && !m_fatherhWnd) {
        WNDCLASS wcex = { 0 };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.lpfnWndProc = WndProc;                         // 设置 窗口回调
        wcex.hInstance = m_hinstance;                       // 设置 模块实例句柄
        wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);    // 设置 默认图标
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);      // 设置 默认光标
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    // 设置 背景颜色
        wcex.lpszMenuName = "";                             // 设置 标题名
        wcex.lpszClassName = szWindowClass;                 // 设置 类名

        if (!RegisterClass(&wcex)) {
            return;
        }
    }

    // 创建窗口
    m_hWnd = CreateWindow(
        szWindowClass,  // 类名
        szTitle,        // 窗口名称
        style,          // 窗口的创建样式
        x,
        y,
        width,
        height,
        m_fatherhWnd,   // 父窗口
        m_menu,         // 菜单栏
        m_hinstance,    // 实例句柄
        (LPVOID)this);  // 额外创建参数

    if (!m_hWnd) {
        return;
    }
}

// 消息控制 - 死循环
void Window::Process() {
    // 显示和更新
    ShowWindow(m_hWnd, isfull ? SW_MAXIMIZE : SW_SHOW);
    UpdateWindow(m_hWnd);

    // 循环消息
    MSG msg = { 0 };
    while (1) {
        // 处理所有win32消息
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                break;
            }
        }
        // 空闲时间
        else {
            
        }
    }

}

// 获取句柄
HWND Window::GetHandle() {
    return this->m_hWnd;
}

// 窗口回调函数
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

// 定义
bool WindowFactory::isMainBuild = false;
HINSTANCE WindowFactory::hinstance = nullptr;

// 设置句柄
void WindowFactory::SethInstance(HINSTANCE _hinstance) {
    hinstance = _hinstance;
}

// 新建一个窗口
// 默认全屏
std::shared_ptr<Window> WindowFactory::Build() {
    std::shared_ptr<Window> result = nullptr;
    if (!isMainBuild) {
        isMainBuild = true;

        // 默认属性
        auto width = GetSystemMetrics(SM_CXSCREEN);
        auto height = GetSystemMetrics(SM_CYSCREEN);
        auto style = WS_POPUP | WS_VISIBLE;

        // 生成
        result = std::make_shared<Window>();
        if (result) {
            result->width = width;
            result->height = height;
            result->style = style;
            result->m_hinstance = hinstance;

            // 创建
            result->Create();
        }
    }
    return result;
}

// 新建一个窗口
// 参数 - 位置和大小
std::shared_ptr<Window> WindowFactory::Build(int x, int y, int width, int height) {
    std::shared_ptr<Window> result = nullptr;
    if (!isMainBuild) {
        isMainBuild = true;

        // 生成
        result = std::make_shared<Window>();
        if (result) {
            result->x = x;
            result->y = y;
            result->width = width;
            result->height = height;
            result->style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
            result->isfull = false;
            result->m_hinstance = hinstance;

            // 创建
            result->Create();
        }
    }
    return result;
}