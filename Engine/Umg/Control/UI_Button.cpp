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
		if (!_image) {
			return false;
		}
		else {
			// ���òü�
			int width = 0;
			int height = 0;
			auto ret = _image->GetImageSize(width, height);
			if (ret && width != 0 && height != 0) {
				auto srcw = width / 4;
				_image->SetCrop(0, 0, srcw, height);
			}

			// ���
			list_image.push_back(_image);
		}

		// ���ð�ť���
		button_style = ButtonStyle_Once;
	}

	SetLocation(x, y);
	SetSize(w, h);
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
		_text->SetLocaiton(window_x, window_y);
		_text->SetSize(window_width, window_height);
		_text->ReSetLayout();
	}
}


// �����¼�
void UI_Button::CheckEvent(unsigned int* param) {
	UI_Base::CheckEvent(param);

	if (window_release || !param) {
		return;
	}

	if (!window_top) {
		return;
	}

	int param_len = param[0];
	if (param_len >= 2) {
		auto message = param[1];
		if (window_mouse) {
			if (message == WM_LBUTTONDOWN) {
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
			else if (message == WM_LBUTTONUP) {
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
			else if (message == WM_MOUSEMOVE) {
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

			// ���òü�
			int width = 0;
			int height = 0;
			auto ret = _image->GetImageSize(width, height);
			if (ret && width != 0 && height != 0) {
				auto srcw = width / 4;
				auto srcx = (button_state - 1) * srcw;
				_image->SetCrop(srcx, 0, srcw, height);
			}

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

// ����λ��
void UI_Button::SetLocation(int x, int y) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;

	// ͼ��
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				_image->SetLocaiton(x, y);
			}
		}
	}

	// �ı�
	if (_text) {
		_text->SetLocaiton(x, y);
	}
}

// ���ô�С
void UI_Button::SetSize(int w, int h) {
	if (window_release) {
		return;
	}

	this->window_width = w;
	this->window_height = h;

	// ͼ��
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				_image->SetSize(w, h);
			}
		}
	}

	// �ı�
	if (_text) {
		_text->SetSize(w, h);
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
