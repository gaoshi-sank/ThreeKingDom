#include "Animation.h"

// 构造
Animation::Animation() {
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
		ListSprite[showIndex]->Draw();
	}
}

// 设置绘制位置
void Animation::SetLocation(int x, int y) {
	this->draw_x = x;
	this->draw_y = y;

	// 全部图片
	for (auto& _sprite : ListSprite) {
		if (_sprite) {
			_sprite->SetLocation(x, y);
		}
	}
}

// 设置绘制大小
void Animation::SetSize(int w, int h) {
	this->draw_width = w;
	this->draw_height = h;

	// 全部图片
	for (auto& _sprite : ListSprite) {
		if (_sprite) {
			_sprite->SetSize(w, h);
		}
	}
}

// 设置旋转
// 暂未实装
void Animation::SetRotate(float angle) {
	
}

// 获取绘制位置
void Animation::GetLocation(int& x, int& y) {
	x = this->draw_x;
	y = this->draw_y;
}

// 获取绘制大小
void Animation::GetSize(int& w, int& h) {
	w = this->draw_width;
	h = this->draw_height;
}

// 获取旋转
// 暂未实装
void Animation::GetRotate(float& angle) {

}

// 计时器回调
void Animation::CallbackFunction() {
	showIndex += 1;
	if (showIndex >= ListSprite.size()) {
		showIndex = 0;
	}
}