#include <Windows.h>
#include "GameMode.h"

// 主函数入口
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int inShowCmd) {
    GameMode::InitGame(hinstance);
    GameMode::RunGame();
    return 0;
}
