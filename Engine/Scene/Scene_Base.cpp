#include "Scene_Base.h"


static unsigned int id = 0x00;

// 构造
Scene_Base::Scene_Base() {
	scene_id = ++id;		// 编号
	scene_type = 0x00;		// 场景类型
	isPrerelease = false;	// 预释放
}

// 析构
Scene_Base::~Scene_Base() {
	
}

// 停止
void Scene_Base::Stop() {
	isPrerelease = true;
}


// 回调函数
void Scene_Base::Callback(std::function<void(int*)> _callback) {
	this->trigger_scene = _callback;
}