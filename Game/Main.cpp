#include <Windows.h>
#include "GameManager.h"

// 主函数入口
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int inShowCmd) {
    GameManager::InitGameManager(hinstance);
    GameManager::RunGameManager();
    return 0;
}
