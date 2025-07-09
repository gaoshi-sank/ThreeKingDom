#include "UI_Button.h"
#include "../UIFactory.h"

// ����
UI_Button::UI_Button() {
	_text = nullptr;
	click_state = 0;
	button_style = ButtonStyle_Once;
	button_state = 0;
	button_index = 0;
	window_style = UIStyle_Button;
}

// ����
UI_Button::~UI_Button() {
	// ͼ��
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				delete _image;
				_image = nullptr;
			}
		}
		list_image.clear();
	}

	// �ı�
	if (_text) {
		delete _text;
		_text = nullptr;
	}
}

void UI_Button::PreRelease() {
	window_release = true;
};

// ����
bool UI_Button::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// ������ͼ�ఴť�������ĸ�״̬��ͼ��
// ������λ�úʹ�С
bool UI_Button::Create(const std::string& filename, int x, int y, int w, int h) {
	if (!Create()) {
		return false;
	}

	if (!filename.empty()) {
		auto _image = new SImage(filename.c_str());
		if (_image) {
			// ����ü�
			auto image = _image->GetImage();
			auto src_rect = D2D1::RectF();	// �ü�����
			_image->SetCrop(src_rect);

			// ���
			list_image.push_back(_image);
		}

		// ���ð�ť���
		button_style = ButtonStyle_Once;
	}

	SetRect(x, y, w, h);
	return true;
}

// �����ĸ�״̬ͼ��
// ��ͨ�������ڣ����£�ʧЧ
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

	// ���ð�ť���
	button_style = ButtonStyle_Four;
	auto ret = true;
	ret &= build_func(out);
	ret &= build_func(in);
	ret &= build_func(down);
	ret &= build_func(disable);

	return ret;
}

// ���Ӿ�̬�ı�
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


// �����¼�
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
			// �����ڰ���
			if (window_inrect) {
				// δ����
				if (click_state == 0) {
					click_state = 1;

					// �����¼�
					if (callback_down) {
						callback_down(window_id);
					}
				}
			}
			// �����ⰴ��
			else {
				// δ����״̬
				click_state = 0;
			}
		}
		else if (eventType == WM_LBUTTONUP) {
			// �����ڷſ�
			if (window_inrect) {
				// ֮ǰ���¹�
				if (click_state == 1) {
					// ��������¼�
					if (callback_click) {
						callback_click(window_id);
					}
				}

				// �����ſ��¼�
				if (callback_up) {
					callback_up(window_id);
				}
			}

			// �޸�״̬
			click_state = 0;
		}
		else if (eventType == WM_MOUSEMOVE) {
			// ���������ƶ�
			if (window_inrect) {
				// ������ͣ�¼�
				if (callback_hover) {
					callback_hover(window_id);
				}
			}
		}
	}
	else if (window_key) {

	}

}

// ����
void UI_Button::Update() {
	if (window_release) {
		return;
	}

	// ����״̬
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

	// ״̬����
	if (!list_image.empty()) {
		if (button_style == ButtonStyle_Once) {
			auto& _image = list_image[0];

			// ����ü�����
			auto image = _image->GetImage();

			// ����
			_image->Update();
		}
		else if (button_style == ButtonStyle_Four) {
			button_index = button_state - 1;
			if (button_index >= 0 && button_index < list_image.size()) {
				list_image[button_index]->Update();
			}
		}
	}
	

	// �ı�
	if (_text) {
		_text->Update();
	}

}

// ����
void UI_Button::Draw() {
	if (window_release) {
		return;
	}

	// ����ͼ��
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

	// �ı�
	if (_text) {
		_text->Draw();
	}

}

// ��������
void UI_Button::SetRect(int x, int y, int width, int height) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;
	this->window_width = width;
	this->window_height = height;

	// ͼ��
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				_image->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
			}
		}
	}

	// �ı�
	if (_text) {
		_text->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
	}
}

// ���ÿɼ���
void UI_Button::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}


// ���ûص�
void UI_Button::Event_Hover(std::function<void(int Id)> _hover) {
	this->callback_hover = _hover;
}

// ���ûص� - ����
void UI_Button::Event_Down(std::function<void(int Id)> _down) {
	this->callback_down = _down;
}

// ���ûص� - �ſ�
void UI_Button::Event_Up(std::function<void(int Id)> _up) {
	this->callback_up = _up;
}

// ���ûص� - ���
void UI_Button::Event_Click(std::function<void(int Id)> _click) {
	this->callback_click = _click;
}
