#include <Windows.h>
#include "Engine/DeviceProvider.h"

// 主函数入口
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int inShowCmd) {

    auto dm = DeviceProvider::GetInstance();
    if (dm) {
        dm->Init(250, 80, 800, 600, "测试Demo");
        dm->Run();
    }
    DeviceProvider::Release();

    return 0;
}
