#include "Scene_Base.h"


static unsigned int id = 0x00;

// ����
Scene_Base::Scene_Base() {
	scene_id = ++id;		// ���
	isPrerelease = false;	// Ԥ�ͷ�

}

// ����
Scene_Base::~Scene_Base() {
	
}

// ֹͣ
void Scene_Base::Stop() {
	isPrerelease = true;
}


// �ص�����
void Scene_Base::Callback(std::function<void(int*)> _callback) {
	this->callback_handle = _callback;
}