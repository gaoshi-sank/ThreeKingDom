#include "GameMode.h"


// ��ʼ����Ϸ
void GameMode::InitGame(HINSTANCE hinstance) {
    LogI("GameMode::InitGame +");

    // ��ʼ������
    EngineProvider::InitEngine(hinstance);

    // ��ʼ����Ϸ���ݿ�
    auto dataeng = DataProvider::GetInstance();
    if (dataeng) {
        dataeng->InitData();
    }

    // ���ӳ�ʼ����
    SceneManager::AddScene(new Scene_Test());


    LogI("GameMode::InitGame -");
}

// ��Ϸ����
void GameMode::RunGame() {
    LogI("GameMode::RunGame +");

    // ��������
    EngineProvider::RunEngine();


    LogI("GameMode::RunGame -");
}