#include "UI_CheckBox.h"
#include "../UIFactory.h"

// 构造
UI_CheckBox::UI_CheckBox() {
	_text = nullptr;
	check_state = 0;
	button_style = CheckBoxStyle_OneOnce;
	button_state = 0;
	button_index = 0;
	window_style = UIStyle_CheckBox;
}

// 析构
UI_CheckBox::~UI_CheckBox() {
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

void UI_CheckBox::PreRelease() {
	window_release = true;
};

// 创建
bool UI_CheckBox::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// 创建单图类按钮
// 参数: 位置和大小
// 参数: 资源风格（4图和2图）
bool UI_CheckBox::Create(const std::string& filename, int x, int y, int w, int h, int resStyle) {
	if (!Create()) {
		return false;
	}

	if (!filename.empty()) {
		// 限制
		int resLine = (resStyle == 4) ? 4 : 2;

		// 生成图像
		auto _image = new SImage(filename.c_str());
		if (_image) {
			auto image = _image->GetImage();

			// 添加
			list_image.push_back(_image);
		}

		// 设置按钮风格
		button_style = CheckBoxStyle_OneOnce;
	}

	SetRect(x, y, w, h);
	return true;
}

// 增加四个状态图像
// 普通，区域内，按下，失效
bool UI_CheckBox::Create(const std::string& out, const std::string& in, const std::string& down, const std::string& disable) {
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
	button_style = CheckBoxStyle_OneFour;
	auto ret = true;
	ret &= build_func(out);
	ret &= build_func(in);
	ret &= build_func(down);
	ret &= build_func(disable);

	return ret;
}

// 增加静态文本
void UI_CheckBox::AddStaticText(const std::string& text) {
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
void UI_CheckBox::CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams) {
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
				check_state = (check_state == 1) ? 0 : 1;

				// 触发复选框事件
				UIFactory::CheckBoxParam(this->window_id, this->group, check_state);

				// 按下事件
				if (callback_down) {
					callback_down(window_id);
				}
			}
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
void UI_CheckBox::Update() {
	if (window_release) {
		return;
	}

	// 更新状态
	// 单图资源类型
	if (button_style == CheckBoxStyle_OneOnce || button_style == CheckBoxStyle_OneFour) {
		if (check_state == 1) {
			button_state = 3;
		}
		else {
			if (window_inrect) {
				button_state = 2;
			}
			else {
				button_state = 1;
			}
		}
	}
	// 切换资源类型
	else if (button_style == CheckBoxStyle_ChangeOp_Once || button_style == CheckBoxStyle_ChangeOp_Two) {
		button_state = 1;
		if (check_state == 1) {
			button_state = 2;
		}
	}

	// 状态更新
	if (!list_image.empty()) {
		if (button_style == CheckBoxStyle_OneOnce || button_style == CheckBoxStyle_ChangeOp_Once) {
			auto& _image = list_image[0];
			int resLine = (button_style == CheckBoxStyle_OneOnce) ? 4 : 2;

			// 重设裁剪
			auto image = _image->GetImage();

			// 更新
			_image->Update();
		}
		else if (button_style == CheckBoxStyle_OneFour || button_style == CheckBoxStyle_ChangeOp_Two) {
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
void UI_CheckBox::Draw() {
	if (window_release) {
		return;
	}

	// 绘制图像
	if (!list_image.empty()) {
		if (button_style == CheckBoxStyle_OneOnce) {
			list_image[0]->Draw();
		}
		else if (button_style == CheckBoxStyle_OneFour) {
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
void UI_CheckBox::SetRect(int x, int y, int width, int height) {
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
void UI_CheckBox::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}

// 设置单选
void UI_CheckBox::SetCheckBoxType(int _type) {
	check_state = _type;
}

// 设置所属组
void UI_CheckBox::SetGroupId(int _id) {
	this->group = _id;
}

// 获取单选状态
bool UI_CheckBox::GetCheckState() {
	return check_state == 1;
}

// 设置回调
void UI_CheckBox::Event_Hover(std::function<void(int Id)> _hover) {
	// this->callback_hover = _hover;
	// 复选框 - 不触发当前事件
}

// 设置回调 - 按下
void UI_CheckBox::Event_Down(std::function<void(int Id)> _down) {
	this->callback_down = _down;
}

// 设置回调 - 放开
void UI_CheckBox::Event_Up(std::function<void(int Id)> _up) {
	// this->callback_up = _up;
	// 复选框 - 不触发当前事件
}

// 设置回调 - 点击
void UI_CheckBox::Event_Click(std::function<void(int Id)> _click) {
	// this->callback_click = _click;
	// 复选框 - 不触发当前事件
}
