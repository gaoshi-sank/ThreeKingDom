#include "Scene_Test.h"
#include "../Engine/Input/InputFactory.h"

// 构造
Scene_Test::Scene_Test() {

}

// 析构
Scene_Test::~Scene_Test() {



}

// 初始化
void Scene_Test::Init() {

}

// 释放
void Scene_Test::Release() {

	

}

// 更新
void Scene_Test::Update() {



}

// 渲染
void Scene_Test::Draw() {



}

// 停止
void Scene_Test::Stop() {
	Scene_Base::Stop();
}

// 事件驱动
void Scene_Test::CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams) {
	if (eventType == WM_KEYDOWN) {
	}
}

// 面板UI事件处理
void Scene_Test::EventControl(int uiType, int ui_id, int msgType, int message) {

}