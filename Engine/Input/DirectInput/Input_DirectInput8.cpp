#include "Input_DirectInput8.h"

// ��ֵӳ��
int GetVKtoDIK(int vk_code) {
    if (vk_code == VK_ESCAPE) {
        return DIK_ESCAPE;
    }
    return 0x00;
}

// ����
Input_DirectInput8::Input_DirectInput8() {
    g_DirectInput = nullptr;
    g_keyboard = nullptr;
    g_mouseboard = nullptr;
}

// ����
Input_DirectInput8::~Input_DirectInput8() {

}

// ����������
bool Input_DirectInput8::BuildInput(HINSTANCE hinstance, HWND hWnd) {
    // DISCL_EXCLUSIVE          ����������Ƴ���ǰ����
    // DISCL_NONEXCLUSIVE       ���һֱ�ɼ�
    // DISCL_FOREGROUND         ��ǰ�����н����ǿ���ȡ�����״̬
    // DISCL_BACKGROUND         ��ʹû�н���
    // DISCL_NOWINKEY           ���ü���Win��


    // ����DirectInput�豸
    HRESULT hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_DirectInput, nullptr);
    if (FAILED(hr)) {
        return false;
    }

    // �����豸 - ����
    hr = g_DirectInput->CreateDevice(GUID_SysKeyboard, &g_keyboard, nullptr);
    if (FAILED(hr)) {
        return false;
    }
    else {
        // ���� - ���ø�ʽ��Э���ȼ�
        if (g_keyboard) {
            hr &= g_keyboard->SetDataFormat(&c_dfDIKeyboard);
            hr &= g_keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
            if (FAILED(hr)) {
                return false;
            }

            // ��ȡȨ��
            g_keyboard->Acquire();
        }
    }

    // �����豸 - ���
    hr = g_DirectInput->CreateDevice(GUID_SysMouse, &g_mouseboard, nullptr);
    if (FAILED(hr)) {
        return false;
    }
    else {
        // ��� - ���ø�ʽ��Э���ȼ�
        if (g_mouseboard) {
            hr &= g_mouseboard->SetDataFormat(&c_dfDIMouse);
            hr &= g_mouseboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
            if (FAILED(hr)) {
                return false;
            }

            // ��ȡȨ��
            g_mouseboard->Acquire();
        }
    }


	return true;
}

// �ͷſ�����
void Input_DirectInput8::Release() {
    // ����
    if (g_keyboard) {
        g_keyboard->Unacquire();
        g_keyboard->Release();      // ����Ҫdelete
        g_keyboard = nullptr;
    }
}

// ��ȡ����״̬
bool Input_DirectInput8::GetKeyState(int _key) {
    HRESULT hr = S_OK;
    BYTE keyboardState[256] = { 0 };
    auto key = GetVKtoDIK(_key);

    // ��ȡ����״̬ 
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

// ��ȡ���״̬
// 0 - ��������1 - ����Ҽ�
bool Input_DirectInput8::GetMouseState(int key) {
    HRESULT hr;
    DIMOUSESTATE mouseboardState = { 0 };

    // ��ȡ����״̬ 
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