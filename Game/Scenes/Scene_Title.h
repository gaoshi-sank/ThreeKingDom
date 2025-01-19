#ifndef _Scene_Title_h_
#define _Scene_Title_h_


#include "SceneInclude.h"

class Scene_Title : public Scene_Base {
private:
	std::shared_ptr<SText> _object;

public:
	// 构造
	Scene_Title();

	// 析构
	~Scene_Title();

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


#endif // !_Scene_Title_h_
