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
    auto first_scene = new Scene_Title();
    if (first_scene) {
        SceneManager::AddScene(first_scene);
        LogI("Add A Scene for Scene_Title");
    }


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

// �����¼�����
// ����ID�������¼����¼�����1,2,3
void GameManager::EventControl_Scene(int* param) {
    if (param) {
        int len = param[0];
        if (len >= 3) {
            unsigned int trigger_Id = (unsigned int)param[1];
            int eventType = param[2];
            int sceneType = param[3];

            // �л�����
            if (eventType == SceneEventType_ChangScene) {
                // ��ǰ����Ϊ "���ⳡ��"
                if (sceneType == SceneType_Title) {
                    // Ψһ��Ϣ - �л���һ������
                    auto nextScene = new Scene_Card();
                    if (nextScene) {
                        // ��ʼ����Ϸ�Ծ�״̬
                        m_gameState = std::make_shared<GameState>();

                        // �л�����
                        auto next_id = nextScene->scene_id;
                        SceneManager::AddScene(nextScene);
                        SceneManager::SwitchScene(next_id);
                    }
                }
            }
        }
    }
}