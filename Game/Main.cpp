#include <Windows.h>
#include "GameMode.h"

// ���������
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int inShowCmd) {
    GameMode::InitGame(hinstance);
    GameMode::RunGame();
    return 0;
}
