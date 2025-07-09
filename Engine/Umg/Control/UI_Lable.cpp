#include "UI_Lable.h"

// 构造
UI_Lable::UI_Lable() {
	_image = nullptr;
	_text = nullptr;
	window_style = UIStyle_Lable;
}

// 析构
UI_Lable::~UI_Lable() {
	// 图像
	if (_image) {
		delete _image;
		_image = nullptr;
	}

	// 文本
	if (_text) {
		delete _text;
		_text = nullptr;
	}
}

void UI_Lable::PreRelease(){
	window_release = true;
};

// 创建
bool UI_Lable::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// 创建图像 
// 参数：位置和大小
bool UI_Lable::Create(const std::string& filename, int x, int y, int w, int h) {
	if (!Create()) {
		return false;
	}

	if (!filename.empty() && !_image) {
		_image = new SImage(filename.c_str());
		if (!_image) {
			return false;
		}
	}

	SetRect(x, y, w, h);
	return true;
}

// 增加静态文本
void UI_Lable::AddStaticText(const std::string& text) {
	if (window_release) {
		return;
	}

	if (!_text) {
		_text = new SText(text.c_str());
	}
	else {
		_text->ReSetText(text.c_str());
	}

	if (_text) {
		_text->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
		_text->ReSetLayout();
	}
}

// 事件驱动
void UI_Lable::CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams) {
	// 标签UI不参与
}


// 更新
void UI_Lable::Update() {
	if (window_release) {
		return;
	}

	// 图像
	if (_image) {
		_image->Update();
	}

	// 文本
	if (_text) {
		_text->Update();
	}

}

// 绘制
void UI_Lable::Draw() {
	if (window_release) {
		return;
	}

	// 图像
	if (_image) {
		_image->Draw();
	}

	// 文本
	if (_text) {
		_text->Draw();
	}

}

// 设置区域
void UI_Lable::SetRect(int x, int y, int width, int height) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;
	this->window_width = width;
	this->window_height = height;

	// 图像
	if (_image) {
		_image->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
	}

	// 文本
	if (_text) {
		_text->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
	}
}

// 设置可见性
void UI_Lable::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}
