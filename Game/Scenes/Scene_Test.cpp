#include "Scene_Test.h"

// 构造
Scene_Test::Scene_Test() {
	scene_type = SceneType_Test;

}

// 析构
Scene_Test::~Scene_Test() {
	Object_List.clear();

}

// 初始化
void Scene_Test::Init() {
	LogI("Scene_Test::Init +");

	

	LogI("Scene_Test::Init -");
}

// 释放
void Scene_Test::Release() {

}

// 更新
void Scene_Test::Update() {
	auto input = InputFactory::GetInstance()->GetInput();
	if (input) {
		// 
		int x = -1, y = -1;
		auto ret_pos = input->GetMousePos(x, y);
		auto ret_leftdown = input->GetMouseState(0);

		// 遍历
		for (auto& Object : Object_List) {
			if (Object) {
				auto& hero = std::dynamic_pointer_cast<Object_Hero>(Object);
				if (ret_pos && (x != -1 && y != -1)) {
					hero->CheckPoint(x, y);
				}

				if (ret_leftdown) {
					hero->CheckDown();
				}
				else{
					hero->CheckUp();
				}
			}
		}
		
	}

	// 更新列表
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
