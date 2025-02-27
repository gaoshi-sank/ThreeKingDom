#include "UI_GIF.h"


// 构造 
UI_GIF::UI_GIF() {
	// 窗口类型 
	this->window_style = UI_Base::UIStyle_Gif;
	_gif = nullptr;
}

// 析构
UI_GIF::~UI_GIF() {

}

// 释放
void UI_GIF::PreRelease() {
	
}

// 创建
bool UI_GIF::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// 创建单个图资源的GIF
bool UI_GIF::Create(const std::string& filename, int rect_x, int rect_y, int rect_width, int rect_height, int cropWidth, int cropHeight, int speed) {
	if (!_gif) {
		_gif = new Animation();
		if (_gif) {
			_gif->CreateByOne(filename.c_str(), rect_x, rect_y, rect_width, rect_height, cropWidth, cropHeight);
			_gif->SetPlaySpeed(speed);
		}
	}
	return Create();
}

// 创建多个图资源的GIF
bool UI_GIF::Create(std::vector<std::string> fileLists, int rect_x, int rect_y, int rect_width, int rect_height, int speed) {
	if (!_gif) {
		_gif = new Animation();
		if (_gif) {
			for (auto& filename : fileLists) {
				if (!filename.empty()) {
					_gif->CreateByMul(filename.c_str(), rect_x, rect_y, rect_width, rect_height);
				}
			}
			_gif->SetPlaySpeed(speed);
		}
	}
	return Create();
}

// 更新事件
void UI_GIF::CheckEvent(unsigned int* param) {

}

// 更新
void UI_GIF::Update() {
	if (window_release) {
		return;
	}

	if (_gif) {
		_gif->Update();
	}
}

// 渲染
void UI_GIF::Draw() {
	if (_gif) {
		_gif->Draw();
	}
}

// 设置位置
void UI_GIF::SetLocation(int x, int y) {
	if (window_release) {
		return;
	}
	this->window_x = x;
	this->window_y = y;

}

// 设置大小
void UI_GIF::SetSize(int w, int h) {
	if (window_release) {
		return;
	}
	this->window_width = w;
	this->window_height = h;
}

// 设置可见性
void UI_GIF::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}
	this->window_visible = visible;
}