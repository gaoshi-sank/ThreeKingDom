#include "Scene_Test.h"
#include "../Engine/Input/InputFactory.h"

// ����
Scene_Test::Scene_Test() {

}

// ����
Scene_Test::~Scene_Test() {



}

// ��ʼ��
void Scene_Test::Init() {

}

// �ͷ�
void Scene_Test::Release() {

	

}

// ����
void Scene_Test::Update() {



}

// ��Ⱦ
void Scene_Test::Draw() {



}

// ֹͣ
void Scene_Test::Stop() {
	Scene_Base::Stop();
}

// �¼�����
void Scene_Test::CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams) {
	if (eventType == WM_KEYDOWN) {
	}
}

// ���UI�¼�����
void Scene_Test::EventControl(int uiType, int ui_id, int msgType, int message) {

}