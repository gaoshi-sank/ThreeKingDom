#include "Object_Hero.h"

// ����
Object_Hero::Object_Hero() {

}

// ����
Object_Hero::~Object_Hero() {

}

// ����
void Object_Hero::Create(int key) {

}

// ��������
void Object_Hero::CreateHero(int x, int y) {
	_test = std::make_shared<SImage>("C:\\Users\\asus\\Pictures\\39\\Hero\\1-1.png");
	if (_test) {
		_test->SetLocation(x, y);
	}
}

// ����
void Object_Hero::Update() {
	if (_test) {
		_test->Update();
	}
}

// ����
void Object_Hero::Draw() {
	if (_test) {
		_test->Draw();
	}
}