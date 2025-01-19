#ifndef _GameManager_h_
#define _GameManager_h_

/*
* 游戏管理
*/


#include <Windows.h>
#include "../Engine/EngineProvider.h"
#include "Scenes/Scene_Test.h"
#include "Datas/DataProvider.h"
#include "GameState.h"				// 游戏状态


// 游戏管理类
class GameManager {
private:
	// 构造
	GameManager();

	// 析构
	~GameManager();

	// 属性
	std::shared_ptr<GameState> m_gameState;

public:
	// 获取游戏管理句柄
	static GameManager* GetInstance();

	// 释放游戏管理
	static void Release();

	// 初始化游戏管理
	static void InitGameManager(HINSTANCE hinstance);

	// 运行游戏管理
	static void RunGameManager();

	// 获取游戏状态实例
	std::shared_ptr<GameState> GetGameState();

};




#endif // !_GameManager_h_
