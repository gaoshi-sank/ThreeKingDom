#include "GameMode.h"

// ��ʼ����Ϸ
void GameMode::InitGame(HINSTANCE hinstance) {
    // ��ʼ������
    EngineProvider::InitEngine(hinstance);

    // ��ʼ����Ϸ���ݿ�
    auto dataeng = DataProvider::GetInstance();
    if (dataeng) {
        dataeng->InitData();
    }

    // ���ӳ�ʼ����
    SceneManager::AddScene(new Scene_Test());
    
}

// ��Ϸ����
void GameMode::RunGame() {
    // ��������
    EngineProvider::RunEngine();

}