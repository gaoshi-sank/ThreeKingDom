#include "GameMode.h"


// 初始化游戏
void GameMode::InitGame(HINSTANCE hinstance) {
    LogI("GameMode::InitGame +");

    // 初始化引擎
    EngineProvider::InitEngine(hinstance);

    // 初始化游戏数据库
    auto dataeng = DataProvider::GetInstance();
    if (dataeng) {
        dataeng->InitData();
    }

    // 增加初始场景
    SceneManager::AddScene(new Scene_Test());


    LogI("GameMode::InitGame -");
}

// 游戏运行
void GameMode::RunGame() {
    LogI("GameMode::RunGame +");

    // 运行引擎
    EngineProvider::RunEngine();


    LogI("GameMode::RunGame -");
}