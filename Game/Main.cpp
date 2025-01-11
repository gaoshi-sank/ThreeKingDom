#include <Windows.h>
#include "../Engine/EngineProvider.h"
#include "Scene_Test.h"

// 主函数入口
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int inShowCmd) {
    EngineProvider::InitEngine(hinstance);
    SceneManager::AddScene(new Scene_Test());
    EngineProvider::RunEngine();
    return 0;
}
