#include "Unit.h"


Unit::Unit() {

}

Unit::~Unit() {
	
}

void Unit::CreateUnit(int x, int y) {
	_image = std::make_shared<Animation>();
	if (_image) {
		std::string path = "C:\\Users\\asus\\Pictures\\39\\Units\\1-1.png";
		for (auto i = 0; i < 8; i++) {
			_image->AddSprite(path.c_str(), 0, 0, 0, 0, 36 * i, 0, 36, 36);
		}
		_image->SetLocation(x, y);
		_image->SetSize(50, 50);
		_image->SetPlaySpeed(8);
	}

}

void Unit::Update() {
	if (_image) {
		_image->Update();
	}
}

void Unit::Draw() {
	if (_image) {
		_image->Draw();
	}
}