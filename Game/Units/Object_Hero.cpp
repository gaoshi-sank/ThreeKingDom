#include "Object_Hero.h"

// 构造
Object_Hero::Object_Hero() {

}

// 析构
Object_Hero::~Object_Hero() {

}

// 创建
void Object_Hero::Create(int key) {

}

// 创建部队
void Object_Hero::CreateHero(int x, int y) {
	_test = std::make_shared<SImage>("C:\\Users\\asus\\Pictures\\39\\Hero\\1-1.png");
	if (_test) {
		_test->SetLocation(x, y);
	}
}

// 更新
void Object_Hero::Update() {
	if (_test) {
		_test->Update();
	}
}

// 绘制
void Object_Hero::Draw() {
	if (_test) {
		_test->Draw();
	}
}