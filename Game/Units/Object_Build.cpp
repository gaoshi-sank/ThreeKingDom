#include "Object_Build.h"



// ����
Object_Build::Object_Build() {

}

// ����
Object_Build::~Object_Build() {

}

// ����
void Object_Build::Create(int key) {

}

// ��������
void Object_Build::CreateBuild(int x, int y) {
	image = std::make_shared<Image_Build>();
	if (image) {
		image->Create(0x01, x, y, 50, 50);
	}
}

// ����
void Object_Build::Update() {
	if (image) {
		image->Update();
	}
}

// ����
void Object_Build::Draw() {
	if (image) {
		image->Draw();
	}
}