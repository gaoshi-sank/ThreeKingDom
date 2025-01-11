#include "Scene_Test.h"

// 构造
Scene_Test::Scene_Test() {

}

// 析构
Scene_Test::~Scene_Test() {
	unitsList.clear();

}

// 初始化
void Scene_Test::Init() {
	auto newobject = std::make_shared<Unit>();
	if (newobject) {
		newobject->CreateUnit(100, 100);
		this->unitsList.push_back(newobject);
	}

	auto newobject2 = std::make_shared<Unit>();
	if (newobject2) {
		newobject2->CreateUnit(200, 100);
		this->unitsList.push_back(newobject2);
	}
}

// 释放
void Scene_Test::Release() {

}

// 更新
void Scene_Test::Update() {
	if (test) {
		test->Update();
	}

	for (auto& unit : unitsList) {
		if (unit) {
			unit->Update();
		}
	}
}

// 渲染
void Scene_Test::Draw() {
	if (test) {
		test->Draw();
	}

	for (auto& unit : unitsList) {
		if (unit) {
			unit->Draw();
		}
	}
}

// 停止
void Scene_Test::Stop() {

}