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
			_image->SetLocaiton(x, y);
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

// ��ʱ���ص�
void Animation::CallbackFunction() {
	showIndex += 1;
	if (showIndex >= ListSprite.size()) {
		showIndex = 0;
	}
}