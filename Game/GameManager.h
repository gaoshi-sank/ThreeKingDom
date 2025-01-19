#ifndef _GameManager_h_
#define _GameManager_h_

/*
* ��Ϸ����
*/


#include <Windows.h>
#include "../Engine/EngineProvider.h"
#include "Datas/DataProvider.h"
#include "GameState.h"				// ��Ϸ״̬
#include "Scenes/Scene_Test.h"		// ���Գ���
#include "Scenes/Scene_Title.h"		// ���ⳡ��
#include "Scenes/Scene_Card.h"		// ��Ϸ����

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

	// �����¼�����
	// ����ID�������¼����¼�����1,2,3
	void EventControl_Scene(int* param);

};




#endif // !_GameManager_h_
