#include "Animation.h"

// ����
Animation::Animation() {
	sameSprite = false;
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
void Animation::CreateByMul(const char* filename, D2D1_RECT_F drawRect, D2D1_RECT_F cropRect) {
	sameSprite = false;
	if (filename) {
		SImage* _image = new SImage(filename);
		if (_image) {
			_image->SetRect(drawRect);
			_image->SetCrop(cropRect);
			ListSprite.push_back(_image);
		}
	}
}

// ����
void Animation::CreateByOne(const char* filename, D2D1_RECT_F drawRect, D2D1_RECT_F cropRect) {

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
		if (sameSprite) {
			SImage* _image = ListSprite[0];
			if (_image) {
				ListSprite[showIndex]->Draw(_image->GetImage());
			}
		}
		else {
			ListSprite[showIndex]->Draw();
		}
	}
}

// ���û�������
void Animation::SetRect(D2D1_RECT_F _rect) {
	// ȫ��ͼƬ
	for (auto& _sprite : ListSprite) {
		if (_sprite) {
			_sprite->SetRect(_rect);
		}
	}
}

// ������ת
void Animation::SetRotate(float angle) {
	// ȫ��ͼƬ
	for (auto& _sprite : ListSprite) {
		if (_sprite) {
			_sprite->SetRotate(angle);
		}
	}
}

// ��ȡͼ��
ID2D1Bitmap* Animation::GetImage() {
	return nullptr;
}

// ��ʱ���ص�
void Animation::CallbackFunction() {
	showIndex += 1;
	if (showIndex >= ListSprite.size()) {
		showIndex = 0;
	}
}