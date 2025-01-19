#include "Object_Hero.h"

// 构造
Object_Hero::Object_Hero() {
	InRect = false;
	inhand_state = 0;
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


// 检查事件
void Object_Hero::CheckPoint(int x, int y) {
	if (_test) {
		InRect = Pos_In_Rect(x, y, _test->draw_x, _test->draw_y, _test->draw_x + _test->draw_height, _test->draw_y + _test->draw_height);
		if (inhand_state == 1) {
			_test->draw_x = x - _test->draw_width / 2;
			_test->draw_y = y - _test->draw_height / 2;
		}
	}
}

void Object_Hero::CheckDown() {
	if (_test && InRect) {
		inhand_state = 1;
	}
}

void Object_Hero::CheckUp() {
	if (_test) {
		inhand_state = 0;
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