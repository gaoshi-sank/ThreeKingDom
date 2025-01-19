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
    SceneManager::AddScene(new Scene_Test());


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