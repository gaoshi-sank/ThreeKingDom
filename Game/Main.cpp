#include <Windows.h>
#include "GameManager.h"

// ���������
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int inShowCmd) {
    GameManager::InitGameManager(hinstance);
    GameManager::RunGameManager();
    return 0;
}
