#ifndef _Scene_Test_h_
#define _Scene_Test_h_


#include "SceneInclude.h"

class Scene_Test : public Scene_Base {
private:
	std::vector<std::shared_ptr<Object_Base>> Object_List;


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


#endif // !_Scene_Test_h_
