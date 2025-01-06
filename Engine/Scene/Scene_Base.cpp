#include "Scene_Base.h"


static unsigned int id = 0x00;

// 构造
Scene_Base::Scene_Base() {
	scene_id = ++id;		// 编号
	isPrerelease = false;	// 预释放

}

// 析构
Scene_Base::~Scene_Base() {
	
}

// 停止
void Scene_Base::Stop() {
	isPrerelease = true;
}