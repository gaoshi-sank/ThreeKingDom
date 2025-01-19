#include "Scene_Card.h"
#include "../GameManager.h"

// ����
Scene_Card::Scene_Card() {
	isResInit = false;
}

// ����
Scene_Card::~Scene_Card() {

}

// ��ʼ��
void Scene_Card::Init() {
	if (isResInit) {
		return;
	}

	// ��ʼ��������Ϸ״̬
	auto gamestate = GameManager::GetInstance()->GetGameState();
	if (gamestate) {
		gamestate->cardState = 0;

	}


	// �ѳ�ʼ��
	isResInit = true;
}

// �ͷ�
void Scene_Card::Release() {

}

// ����
void Scene_Card::Update() {
	auto gamestate = GameManager::GetInstance()->GetGameState();
	if (gamestate) {
	
		// ׼��״̬
		if (gamestate->cardState == 0) {
			Init();
			gamestate->cardState = 1;
		}
		// ��ʼ��״̬
		else if (gamestate->cardState == 1) {


			gamestate->cardState = 2;
		}
		// ��Ϸѭ��״̬
		else if (gamestate->cardState == 2) {

		}
		// ����״̬
		else if (gamestate->cardState == 3) {

		}

	}
}

// ��Ⱦ
void Scene_Card::Draw() {
	auto gamestate = GameManager::GetInstance()->GetGameState();
	if (gamestate) {
		// ��Ϸѭ��״̬
		if (gamestate->cardState == 2) {

		}
	}
}

// ֹͣ
void Scene_Card::Stop() {

}