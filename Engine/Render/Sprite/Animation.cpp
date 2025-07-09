#include "Animation.h"

// 构造
Animation::Animation() {
	sameSprite = false;
	showIndex = 0;
	_timer = nullptr;

}

// 析构
Animation::~Animation() {
	// 计时器
	if (_timer) {
		_timer->exit();
	}

	// 图像
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

// 创建
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

// 创建
void Animation::CreateByOne(const char* filename, D2D1_RECT_F drawRect, D2D1_RECT_F cropRect) {

}

// 创建
void Animation::AddSprite(SImage* _newsprite) {
	if (_newsprite) {
		ListSprite.push_back(_newsprite);
	}
}

// 设置播放速率
// 速率大于0
void Animation::SetPlaySpeed(int number) {
	if (!_timer && (number >= 1 && number <= 120)) {
		_timer = TimerFactory::SetTimer([&](int* ) {
			CallbackFunction();
		}, 1000 * 1.0f / number, true);
	}
}

// 更新
void Animation::Update() {
	if (showIndex >= 0 && showIndex < ListSprite.size()) {
		ListSprite[showIndex]->Update();
	}
}

// 绘制
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

// 设置绘制区域
void Animation::SetRect(D2D1_RECT_F _rect) {
	// 全部图片
	for (auto& _sprite : ListSprite) {
		if (_sprite) {
			_sprite->SetRect(_rect);
		}
	}
}

// 设置旋转
void Animation::SetRotate(float angle) {
	// 全部图片
	for (auto& _sprite : ListSprite) {
		if (_sprite) {
			_sprite->SetRotate(angle);
		}
	}
}

// 获取图像
ID2D1Bitmap* Animation::GetImage() {
	return nullptr;
}

// 计时器回调
void Animation::CallbackFunction() {
	showIndex += 1;
	if (showIndex >= ListSprite.size()) {
		showIndex = 0;
	}
}