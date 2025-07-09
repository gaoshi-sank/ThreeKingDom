#include "../Engine/EngineProvider.h"
#include "Scene_Test.h"

// Ö÷º¯Êý
int APIENTRY wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow)
{
    EngineProvider::InitEngine(hInstance, false, 800, 600);

    SceneManager::AddScene(new Scene_Test());

    EngineProvider::RunEngine();
    return 0;
}