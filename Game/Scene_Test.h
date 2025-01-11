#ifndef _Scene_Test_h_
#define _Scene_Test_h_


#include "../Engine/Scene/SceneManager.h"
#include "Unit.h"

class Scene_Test : public Scene_Base {
private:
	std::shared_ptr<Blut> test;
	std::vector<std::shared_ptr<Unit>> unitsList;

public:
	// 构造
	Scene_Test();

	// 析构
	~Scene_Test();

	// 初始化
	virtual void Init();

	// 释放
	virtual void Release();

	// 更新
	virtual void Update();

	// 渲染
	virtual void Draw();

	// 停止
	virtual void Stop();
};


#endif // !1
