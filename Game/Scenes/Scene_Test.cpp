#include "Scene_Test.h"

// 构造
Scene_Test::Scene_Test() {

}

// 析构
Scene_Test::~Scene_Test() {
	Object_List.clear();

}

// 初始化
void Scene_Test::Init() {
	LogI("Scene_Test::Init +");

	auto newobject = std::make_shared<Object_Army>();
	if (newobject) {
		newobject->CreateAmry(100, 100);
		this->Object_List.push_back(newobject);
	}
	LogI("Scene_Test::Init CreateAmry");

	auto newobject2 = std::make_shared<Object_Army>();
	if (newobject2) {
		newobject2->CreateAmry(200, 100);
		newobject2->SetFace(4);
		this->Object_List.push_back(newobject2);
	}
	LogI("Scene_Test::Init CreateAmry 2");

	auto newobject3 = std::make_shared<Object_Build>();
	if (newobject3) {
		newobject3->CreateBuild(320, 172);
		this->Object_List.push_back(newobject3);
	}
	LogI("Scene_Test::Init CreateBuild");

	auto newobject4 = std::make_shared<Object_Hero>();
	if (newobject4) {
		newobject4->CreateHero(150, 300);
		this->Object_List.push_back(newobject4);
	}
	LogI("Scene_Test::Init CreateHero");

	LogI("Scene_Test::Init -");
}

// 释放
void Scene_Test::Release() {

}

// 更新
void Scene_Test::Update() {
	for (auto& Object: Object_List) {
		if (Object) {
			Object->Update();
		}
	}
}

// 渲染
void Scene_Test::Draw() {
	for (auto& Object : Object_List) {
		if (Object) {
			Object->Draw();
		}
	}
}

// 停止
void Scene_Test::Stop() {

}