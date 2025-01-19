#include "GameManager.h"

// 静态值
static GameManager* g_gm = nullptr;

// 构造
GameManager::GameManager() {
    m_gameState = std::make_shared<GameState>();

}

// 析构
GameManager::~GameManager() {

}

// 获取游戏管理句柄
GameManager* GameManager::GetInstance() {
    if (!g_gm) {
        g_gm = new GameManager();
    }
    return g_gm;
}

// 释放游戏管理
void GameManager::Release() {
    if (g_gm) {
        delete g_gm;
        g_gm = nullptr;
    }
}

// 初始化游戏管理
void GameManager::InitGameManager(HINSTANCE hinstance) {
    LogI("GameManager InitGameManager +");

    // 初始化引擎
    EngineProvider::InitEngine(hinstance);

    // 初始化游戏数据库
    auto dataeng = DataProvider::GetInstance();
    if (dataeng) {
        dataeng->InitData();
    }

    // 增加初始场景
    auto first_scene = new Scene_Title();
    if (first_scene) {
        SceneManager::AddScene(first_scene);
        LogI("Add A Scene for Scene_Title");
    }


    LogI("GameManager InitGameManager -");
}

// 运行游戏管理
void GameManager::RunGameManager() {
    LogI("GameManager RunGameManager +");

    // 运行引擎
    EngineProvider::RunEngine();


    LogI("GameManager RunGameManager -");
}

// 获取游戏状态实例
std::shared_ptr<GameState> GameManager::GetGameState() {
    return m_gameState;
}

// 场景事件处理
// 场景ID，场景事件，事件参数1,2,3
void GameManager::EventControl_Scene(int* param) {
    if (param) {
        int len = param[0];
        if (len >= 3) {
            unsigned int trigger_Id = (unsigned int)param[1];
            int eventType = param[2];
            int sceneType = param[3];

            // 切换场景
            if (eventType == SceneEventType_ChangScene) {
                // 当前场景为 "标题场景"
                if (sceneType == SceneType_Title) {
                    // 唯一消息 - 切换下一个场景
                    auto nextScene = new Scene_Card();
                    if (nextScene) {
                        // 初始化游戏对局状态
                        m_gameState = std::make_shared<GameState>();

                        // 切换场景
                        auto next_id = nextScene->scene_id;
                        SceneManager::AddScene(nextScene);
                        SceneManager::SwitchScene(next_id);
                    }
                }
            }
        }
    }
}