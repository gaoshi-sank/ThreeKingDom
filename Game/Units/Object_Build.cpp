#include "Object_Build.h"



// 构造
Object_Build::Object_Build() {

}

// 析构
Object_Build::~Object_Build() {

}

// 创建
void Object_Build::Create(int key) {

}

// 创建建筑
void Object_Build::CreateBuild(int x, int y) {
	image = std::make_shared<Image_Build>();
	if (image) {
		image->Create(0x01, x, y, 50, 50);
	}
}

// 更新
void Object_Build::Update() {
	if (image) {
		image->Update();
	}
}

// 绘制
void Object_Build::Draw() {
	if (image) {
		image->Draw();
	}
}