#ifndef _Scene_Card_h_
#define _Scene_Card_h_


#include "SceneInclude.h"

class Scene_Card : public Scene_Base {
private:
	std::vector<std::shared_ptr<Object_Base>> Object_List;
	bool isResInit;

public:
	// 构造
	Scene_Card();

	// 析构
	~Scene_Card();

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


#endif // !_Scene_Card_h_
