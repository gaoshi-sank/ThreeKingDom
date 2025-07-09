#include "UI_Button.h"
#include "../UIFactory.h"

// 构造
UI_Button::UI_Button() {
	_text = nullptr;
	click_state = 0;
	button_style = ButtonStyle_Once;
	button_state = 0;
	button_index = 0;
	window_style = UIStyle_Button;
}

// 析构
UI_Button::~UI_Button() {
	// 图像
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				delete _image;
				_image = nullptr;
			}
		}
		list_image.clear();
	}

	// 文本
	if (_text) {
		delete _text;
		_text = nullptr;
	}
}

void UI_Button::PreRelease() {
	window_release = true;
};

// 创建
bool UI_Button::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// 创建单图类按钮（包含四个状态的图像）
// 参数：位置和大小
bool UI_Button::Create(const std::string& filename, int x, int y, int w, int h) {
	if (!Create()) {
		return false;
	}

	if (!filename.empty()) {
		auto _image = new SImage(filename.c_str());
		if (_image) {
			// 重设裁剪
			auto image = _image->GetImage();
			auto src_rect = D2D1::RectF();	// 裁剪区域
			_image->SetCrop(src_rect);

			// 添加
			list_image.push_back(_image);
		}

		// 设置按钮风格
		button_style = ButtonStyle_Once;
	}

	SetRect(x, y, w, h);
	return true;
}

// 增加四个状态图像
// 普通，区域内，按下，失效
bool UI_Button::Create(const std::string& out, const std::string& in, const std::string& down, const std::string& disable) {
	if (!Create()) {
		return false;
	}

	auto build_func = [&](const std::string& filename) {
		auto _image = new SImage(filename.c_str());
		if (!_image) {
			return false;
		}
		else {
			list_image.push_back(_image);
		}
		return true;
	};

	// 设置按钮风格
	button_style = ButtonStyle_Four;
	auto ret = true;
	ret &= build_func(out);
	ret &= build_func(in);
	ret &= build_func(down);
	ret &= build_func(disable);

	return ret;
}

// 增加静态文本
void UI_Button::AddStaticText(const std::string& text) {
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


// 更新事件
void UI_Button::CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams) {
	UI_Base::CheckEvent(eventType, eventParams);

	if (window_release || eventParams.empty()) {
		return;
	}

	if (!window_top) {
		return;
	}

	if (window_mouse) {
		if (eventType == WM_LBUTTONDOWN) {
			// 区域内按下
			if (window_inrect) {
				// 未按下
				if (click_state == 0) {
					click_state = 1;

					// 按下事件
					if (callback_down) {
						callback_down(window_id);
					}
				}
			}
			// 区域外按下
			else {
				// 未按下状态
				click_state = 0;
			}
		}
		else if (eventType == WM_LBUTTONUP) {
			// 区域内放开
			if (window_inrect) {
				// 之前按下过
				if (click_state == 1) {
					// 出发点击事件
					if (callback_click) {
						callback_click(window_id);
					}
				}

				// 出发放开事件
				if (callback_up) {
					callback_up(window_id);
				}
			}

			// 修改状态
			click_state = 0;
		}
		else if (eventType == WM_MOUSEMOVE) {
			// 在区域内移动
			if (window_inrect) {
				// 触发悬停事件
				if (callback_hover) {
					callback_hover(window_id);
				}
			}
		}
	}
	else if (window_key) {

	}

}

// 更新
void UI_Button::Update() {
	if (window_release) {
		return;
	}

	// 更新状态
	if (window_inrect) {
		if (click_state == 1) {
			button_state = 3;
		}
		else {
			button_state = 2;
		}
	}
	else {
		button_state = 1;
	}

	// 状态更新
	if (!list_image.empty()) {
		if (button_style == ButtonStyle_Once) {
			auto& _image = list_image[0];

			// 重设裁剪区域
			auto image = _image->GetImage();

			// 更新
			_image->Update();
		}
		else if (button_style == ButtonStyle_Four) {
			button_index = button_state - 1;
			if (button_index >= 0 && button_index < list_image.size()) {
				list_image[button_index]->Update();
			}
		}
	}
	

	// 文本
	if (_text) {
		_text->Update();
	}

}

// 绘制
void UI_Button::Draw() {
	if (window_release) {
		return;
	}

	// 绘制图像
	if (!list_image.empty()) {
		if (button_style == ButtonStyle_Once) {
			list_image[0]->Draw();
		}
		else if (button_style == ButtonStyle_Four) {
			if (button_index >= 0 && button_index < list_image.size()) {
				list_image[button_index]->Draw();
			}
		}
	}

	// 文本
	if (_text) {
		_text->Draw();
	}

}

// 设置区域
void UI_Button::SetRect(int x, int y, int width, int height) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;
	this->window_width = width;
	this->window_height = height;

	// 图像
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				_image->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
			}
		}
	}

	// 文本
	if (_text) {
		_text->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
	}
}

// 设置可见性
void UI_Button::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}


// 设置回调
void UI_Button::Event_Hover(std::function<void(int Id)> _hover) {
	this->callback_hover = _hover;
}

// 设置回调 - 按下
void UI_Button::Event_Down(std::function<void(int Id)> _down) {
	this->callback_down = _down;
}

// 设置回调 - 放开
void UI_Button::Event_Up(std::function<void(int Id)> _up) {
	this->callback_up = _up;
}

// 设置回调 - 点击
void UI_Button::Event_Click(std::function<void(int Id)> _click) {
	this->callback_click = _click;
}
