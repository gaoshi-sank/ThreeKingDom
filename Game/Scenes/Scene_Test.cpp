#include "Scene_Test.h"

// ����
Scene_Test::Scene_Test() {
	scene_type = SceneType_Test;

}

// ����
Scene_Test::~Scene_Test() {
	Object_List.clear();

}

// ��ʼ��
void Scene_Test::Init() {
	LogI("Scene_Test::Init +");

	

	LogI("Scene_Test::Init -");
}

// �ͷ�
void Scene_Test::Release() {

}

// ����
void Scene_Test::Update() {
	auto input = InputFactory::GetInstance()->GetInput();
	if (input) {
		// 
		int x = -1, y = -1;
		auto ret_pos = input->GetMousePos(x, y);
		auto ret_leftdown = input->GetMouseState(0);

		// ����
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

	// �����б�
	for (auto& Object: Object_List) {
		if (Object) {
			Object->Update();
		}
	}
}

// ��Ⱦ
void Scene_Test::Draw() {
	for (auto& Object : Object_List) {
		if (Object) {
			Object->Draw();
		}
	}
}

// ֹͣ
void Scene_Test::Stop() {

}
