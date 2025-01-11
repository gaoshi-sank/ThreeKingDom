#include "Scene_Test.h"

// ����
Scene_Test::Scene_Test() {

}

// ����
Scene_Test::~Scene_Test() {
	unitsList.clear();

}

// ��ʼ��
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

// �ͷ�
void Scene_Test::Release() {

}

// ����
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

// ��Ⱦ
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

// ֹͣ
void Scene_Test::Stop() {

}