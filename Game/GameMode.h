#ifndef _GameMode_h_
#define _GameMode_h_

#include <Windows.h>
#include "../Engine/EngineProvider.h"
#include "Scenes/Scene_Test.h"
#include "Datas/DataProvider.h"

class GameMode {
public:
	// ��ʼ����Ϸ
	static void InitGame(HINSTANCE hinstance);

	// ��Ϸ����
	static void RunGame();

};



#endif // !_GameMode_h_
