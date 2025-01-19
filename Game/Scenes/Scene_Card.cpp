#include "Scene_Card.h"
#include "../GameManager.h"

// 构造
Scene_Card::Scene_Card() {
	isResInit = false;
}

// 析构
Scene_Card::~Scene_Card() {

}

// 初始化
void Scene_Card::Init() {
	if (isResInit) {
		return;
	}

	// 初始化本局游戏状态
	auto gamestate = GameManager::GetInstance()->GetGameState();
	if (gamestate) {
		gamestate->cardState = 0;

	}


	// 已初始化
	isResInit = true;
}

// 释放
void Scene_Card::Release() {

}

// 更新
void Scene_Card::Update() {
	auto gamestate = GameManager::GetInstance()->GetGameState();
	if (gamestate) {
	
		// 准备状态
		if (gamestate->cardState == 0) {
			Init();
			gamestate->cardState = 1;
		}
		// 初始化状态
		else if (gamestate->cardState == 1) {


			gamestate->cardState = 2;
		}
		// 游戏循环状态
		else if (gamestate->cardState == 2) {

		}
		// 结束状态
		else if (gamestate->cardState == 3) {

		}

	}
}

// 渲染
void Scene_Card::Draw() {
	auto gamestate = GameManager::GetInstance()->GetGameState();
	if (gamestate) {
		// 游戏循环状态
		if (gamestate->cardState == 2) {

		}
	}
}

// 停止
void Scene_Card::Stop() {

}