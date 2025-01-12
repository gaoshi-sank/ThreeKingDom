#include "Object_Army.h"

// 构造
Object_Army::Object_Army() {

}

// 析构
Object_Army::~Object_Army() {
	
}

// 创建
void Object_Army::Create(int key) {

}

// 创建部队
void Object_Army::CreateAmry(int x, int y) {
	image = std::make_shared<Image_Army>();
	if (image) {
		image->Create(0x01, x, y, 50, 50);
	}
}

// 设置面向方向
void Object_Army::SetFace(int face) {
	if (image) {
		image->SetFace(face);
	}
}

// 更新
void Object_Army::Update() {
	if (image) {
		image->Update();
	}
}

// 绘制
void Object_Army::Draw() {
	if (image) {
		image->Draw();
	}
}