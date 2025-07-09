#ifndef _Scene_Base_h_
#define _Scene_Base_h_

#include "../EngineConfig.h"

// 基础场景类 - 抽象类
// 需要重载 - 初始化、释放、更新、绘制、停止
class Scene_Base {
public:
	unsigned int scene_id;
	int scene_type;
	bool isPrerelease;
	std::function<void(int*)> trigger_scene;

public:
	// 构造
	Scene_Base();

	// 析构
	virtual ~Scene_Base();

	// 初始化
	virtual void Init() = 0;

	// 释放
	virtual void Release() = 0;

	// 更新
	virtual void Update() = 0;

	// 渲染
	virtual void Draw() = 0;

	// 停止
	virtual void Stop() = 0;

	// 事件驱动
	virtual void CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams) = 0;

	// 回调函数
	virtual void Callback(std::function<void(int*)> _callback);
};

#endif // !_Scene_Base_h_
