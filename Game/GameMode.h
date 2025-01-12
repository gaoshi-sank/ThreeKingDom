#ifndef _GameMode_h_
#define _GameMode_h_

#include <Windows.h>
#include "../Engine/EngineProvider.h"
#include "Scenes/Scene_Test.h"
#include "Datas/DataProvider.h"

class GameMode {
public:
	// 初始化游戏
	static void InitGame(HINSTANCE hinstance);

	// 游戏运行
	static void RunGame();

};



#endif // !_GameMode_h_
