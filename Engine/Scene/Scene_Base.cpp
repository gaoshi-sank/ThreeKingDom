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