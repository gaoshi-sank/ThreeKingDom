#ifndef _GameManager_h_
#define _GameManager_h_

/*
* ��Ϸ����
*/


#include <Windows.h>
#include "../Engine/EngineProvider.h"
#include "Scenes/Scene_Test.h"
#include "Datas/DataProvider.h"
#include "GameState.h"				// ��Ϸ״̬


// ��Ϸ������
class GameManager {
private:
	// ����
	GameManager();

	// ����
	~GameManager();

	// ����
	std::shared_ptr<GameState> m_gameState;

public:
	// ��ȡ��Ϸ������
	static GameManager* GetInstance();

	// �ͷ���Ϸ����
	static void Release();

	// ��ʼ����Ϸ����
	static void InitGameManager(HINSTANCE hinstance);

	// ������Ϸ����
	static void RunGameManager();

	// ��ȡ��Ϸ״̬ʵ��
	std::shared_ptr<GameState> GetGameState();

};




#endif // !_GameManager_h_
