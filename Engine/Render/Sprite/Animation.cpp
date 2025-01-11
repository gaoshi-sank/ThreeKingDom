#include "Animation.h"

// ����
Animation::Animation() {
	showIndex = 0;
	_timer = nullptr;

}

// ����
Animation::~Animation() {
	// ��ʱ��
	if (_timer) {
		_timer->exit();
	}

	// ͼ��
	if (!ListSprite.empty()) {
		for (auto& sprite : ListSprite) {
			if (sprite) {
				delete sprite;
				sprite = nullptr;
			}
		}
		ListSprite.clear();
	}
}

// ����
void Animation::AddSprite(const char* filename, int x, int y, int width, int height, int cropx, int cropy, int cropwidth, int cropheight) {
	if(filename) {
		SImage* _image = new SImage(filename);
		if (_image) {
			_image->SetLocation(x, y);
			_image->SetSize(width, height);
			_image->SetCrop(cropx, cropy, cropwidth, cropheight);
		}
		ListSprite.push_back(_image);
	}
}

// ����
void Animation::AddSprite(SImage* _newsprite) {
	if (_newsprite) {
		ListSprite.push_back(_newsprite);
	}
}

// ���ò�������
// ���ʴ���0
void Animation::SetPlaySpeed(int number) {
	if (!_timer && (number >= 1 && number <= 120)) {
		_timer = TimerFactory::SetTimer([&](int* ) {
			CallbackFunction();
		}, 1000 * 1.0f / number, true);
	}
}

// ����
void Animation::Update() {
	if (showIndex >= 0 && showIndex < ListSprite.size()) {
		ListSprite[showIndex]->Update();
	}
}

// ����
void Animation::Draw() {
	if (showIndex >= 0 && showIndex < ListSprite.size()) {
		ListSprite[showIndex]->Draw();
	}
}

// ���û���λ��
void Animation::SetLocation(int x, int y) {
	this->draw_x = x;
	this->draw_y = y;

	// ȫ��ͼƬ
	for (auto& _sprite : ListSprite) {
		if (_sprite) {
			_sprite->SetLocation(x, y);
		}
	}
}

// ���û��ƴ�С
void Animation::SetSize(int w, int h) {
	this->draw_width = w;
	this->draw_height = h;

	// ȫ��ͼƬ
	for (auto& _sprite : ListSprite) {
		if (_sprite) {
			_sprite->SetSize(w, h);
		}
	}
}

// ������ת
// ��δʵװ
void Animation::SetRotate(float angle) {
	
}

// ��ȡ����λ��
void Animation::GetLocation(int& x, int& y) {
	x = this->draw_x;
	y = this->draw_y;
}

// ��ȡ���ƴ�С
void Animation::GetSize(int& w, int& h) {
	w = this->draw_width;
	h = this->draw_height;
}

// ��ȡ��ת
// ��δʵװ
void Animation::GetRotate(float& angle) {

}

// ��ʱ���ص�
void Animation::CallbackFunction() {
	showIndex += 1;
	if (showIndex >= ListSprite.size()) {
		showIndex = 0;
	}
}