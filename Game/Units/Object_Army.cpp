#include "Object_Army.h"

// ����
Object_Army::Object_Army() {

}

// ����
Object_Army::~Object_Army() {
	
}

// ����
void Object_Army::Create(int key) {

}

// ��������
void Object_Army::CreateAmry(int x, int y) {
	image = std::make_shared<Image_Army>();
	if (image) {
		image->Create(0x01, x, y, 50, 50);
	}
}

// ����������
void Object_Army::SetFace(int face) {
	if (image) {
		image->SetFace(face);
	}
}

// ����
void Object_Army::Update() {
	if (image) {
		image->Update();
	}
}

// ����
void Object_Army::Draw() {
	if (image) {
		image->Draw();
	}
}