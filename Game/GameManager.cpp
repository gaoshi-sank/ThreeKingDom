#include "GameManager.h"

// ��ֵ̬
static GameManager* g_gm = nullptr;

// ����
GameManager::GameManager() {
    m_gameState = std::make_shared<GameState>();

}

// ����
GameManager::~GameManager() {

}

// ��ȡ��Ϸ������
GameManager* GameManager::GetInstance() {
    if (!g_gm) {
        g_gm = new GameManager();
    }
    return g_gm;
}

// �ͷ���Ϸ����
void GameManager::Release() {
    if (g_gm) {
        delete g_gm;
        g_gm = nullptr;
    }
}

// ��ʼ����Ϸ����
void GameManager::InitGameManager(HINSTANCE hinstance) {
    LogI("GameManager InitGameManager +");

    // ��ʼ������
    EngineProvider::InitEngine(hinstance);

    // ��ʼ����Ϸ���ݿ�
    auto dataeng = DataProvider::GetInstance();
    if (dataeng) {
        dataeng->InitData();
    }

    // ���ӳ�ʼ����
    SceneManager::AddScene(new Scene_Test());


    LogI("GameManager InitGameManager -");
}

// ������Ϸ����
void GameManager::RunGameManager() {
    LogI("GameManager RunGameManager +");

    // ��������
    EngineProvider::RunEngine();


    LogI("GameManager RunGameManager -");
}

// ��ȡ��Ϸ״̬ʵ��
std::shared_ptr<GameState> GameManager::GetGameState() {
    return m_gameState;
}