#include "Scene_Title.h"
#include "../GameManager.h"

// 构造
Scene_Title::Scene_Title() {
	scene_type = SceneType_Title;
}

// 析构
Scene_Title::~Scene_Title() {

}

// 初始化
void Scene_Title::Init() {
	_object = std::make_shared<SText>();
	if (_object) {
		_object->ReSetText("点击任意键开始游戏");
		_object->ReSetColor(255, 255, 0);
		_object->ReSetLayout();
		_object->SetLocation(200, 200);
		_object->SetSize(200, 50);
	}
}

// 释放
void Scene_Title::Release() {

}

// 更新
void Scene_Title::Update() {

	auto input = InputFactory::GetInstance()->GetInput();
	if (input) {
		auto ret_leftdown = input->GetMouseState(0);
		if (ret_leftdown) {
			// 获取游戏管理句柄
			auto handle = GameManager::GetInstance();
			if (handle) {
				int* param = new int[4];
				if (param) {
					param[0] = 4;
					param[1] = this->scene_id;
					param[2] = SceneEventType_ChangScene;
					param[3] = scene_type;
					handle->EventControl_Scene(param);

					delete[] param;
					param = nullptr;
				}
			}
		}
	}


	if (_object) {
		_object->Update();
	}
}

// 渲染
void Scene_Title::Draw() {
	if (_object) {
		_object->Draw();
	}
}

// 停止
void Scene_Title::Stop() {

}