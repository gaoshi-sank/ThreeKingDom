#include "Input_DirectInput8.h"

// 键值映射
int GetVKtoDIK(int vk_code) {
    if (vk_code == VK_ESCAPE) {
        return DIK_ESCAPE;
    }
    return 0x00;
}

// 构造
Input_DirectInput8::Input_DirectInput8() {
    g_DirectInput = nullptr;
    g_keyboard = nullptr;
    g_mouseboard = nullptr;
}

// 析构
Input_DirectInput8::~Input_DirectInput8() {

}

// 建立控制器
bool Input_DirectInput8::BuildInput(HINSTANCE hinstance, HWND hWnd) {
    // DISCL_EXCLUSIVE          不允许鼠标移出当前窗体
    // DISCL_NONEXCLUSIVE       鼠标一直可见
    // DISCL_FOREGROUND         当前窗口有焦点是可以取得鼠标状态
    // DISCL_BACKGROUND         即使没有焦点
    // DISCL_NOWINKEY           禁用键盘Win键


    // 创建DirectInput设备
    HRESULT hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_DirectInput, nullptr);
    if (FAILED(hr)) {
        return false;
    }

    // 创建设备 - 键盘
    hr = g_DirectInput->CreateDevice(GUID_SysKeyboard, &g_keyboard, nullptr);
    if (FAILED(hr)) {
        return false;
    }
    else {
        // 键盘 - 设置格式和协作等级
        if (g_keyboard) {
            hr &= g_keyboard->SetDataFormat(&c_dfDIKeyboard);
            hr &= g_keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
            if (FAILED(hr)) {
                return false;
            }

            // 获取权限
            g_keyboard->Acquire();
        }
    }

    // 创建设备 - 鼠标
    hr = g_DirectInput->CreateDevice(GUID_SysMouse, &g_mouseboard, nullptr);
    if (FAILED(hr)) {
        return false;
    }
    else {
        // 鼠标 - 设置格式和协作等级
        if (g_mouseboard) {
            hr &= g_mouseboard->SetDataFormat(&c_dfDIMouse);
            hr &= g_mouseboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
            if (FAILED(hr)) {
                return false;
            }

            // 获取权限
            g_mouseboard->Acquire();
        }
    }


	return true;
}

// 释放控制器
void Input_DirectInput8::Release() {
    // 键盘
    if (g_keyboard) {
        g_keyboard->Unacquire();
        g_keyboard->Release();      // 不需要delete
        g_keyboard = nullptr;
    }
}

// 获取键盘状态
bool Input_DirectInput8::GetKeyState(int _key) {
    HRESULT hr = S_OK;
    BYTE keyboardState[256] = { 0 };
    auto key = GetVKtoDIK(_key);

    // 读取键盘状态 
    if (g_keyboard) {
        memset(keyboardState, 0, sizeof(BYTE) * 256);
        hr = g_keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
        if (FAILED(hr)) {
            if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
                hr = g_keyboard->Acquire();
                if (FAILED(hr)) {
                    return false;
                }
            }
        }

        if ((key >= 0x01 && key <= 0xED) && (keyboardState[key] & 0x80)) {
            return true;
        }
    }

    return false;
}

// 获取鼠标状态
// 0 - 鼠标左键，1 - 鼠标右键
bool Input_DirectInput8::GetMouseState(int key) {
    HRESULT hr;
    DIMOUSESTATE mouseboardState = { 0 };

    // 读取键盘状态 
    if (g_mouseboard) {
        hr = g_mouseboard->GetDeviceState(sizeof(mouseboardState), (LPVOID)&mouseboardState);
        if (FAILED(hr)) {
            if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
                hr = g_keyboard->Acquire();
                if (FAILED(hr)) {
                    return false;
                }
            }
        }

        if ((key >= 0 && key <= 4) && (mouseboardState.rgbButtons[key] & 0x80)) {
            return true;
        }
    }

    return false;
}