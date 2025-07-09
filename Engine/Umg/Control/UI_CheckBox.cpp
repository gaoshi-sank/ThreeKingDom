#include "UI_CheckBox.h"
#include "../UIFactory.h"

// ����
UI_CheckBox::UI_CheckBox() {
	_text = nullptr;
	check_state = 0;
	button_style = CheckBoxStyle_OneOnce;
	button_state = 0;
	button_index = 0;
	window_style = UIStyle_CheckBox;
}

// ����
UI_CheckBox::~UI_CheckBox() {
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

void UI_CheckBox::PreRelease() {
	window_release = true;
};

// ����
bool UI_CheckBox::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// ������ͼ�ఴť
// ����: λ�úʹ�С
// ����: ��Դ���4ͼ��2ͼ��
bool UI_CheckBox::Create(const std::string& filename, int x, int y, int w, int h, int resStyle) {
	if (!Create()) {
		return false;
	}

	if (!filename.empty()) {
		// ����
		int resLine = (resStyle == 4) ? 4 : 2;

		// ����ͼ��
		auto _image = new SImage(filename.c_str());
		if (_image) {
			auto image = _image->GetImage();

			// ���
			list_image.push_back(_image);
		}

		// ���ð�ť���
		button_style = CheckBoxStyle_OneOnce;
	}

	SetRect(x, y, w, h);
	return true;
}

// �����ĸ�״̬ͼ��
// ��ͨ�������ڣ����£�ʧЧ
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

	// ���ð�ť���
	button_style = CheckBoxStyle_OneFour;
	auto ret = true;
	ret &= build_func(out);
	ret &= build_func(in);
	ret &= build_func(down);
	ret &= build_func(disable);

	return ret;
}

// ���Ӿ�̬�ı�
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


// �����¼�
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
			// �����ڰ���
			if (window_inrect) {
				check_state = (check_state == 1) ? 0 : 1;

				// ������ѡ���¼�
				UIFactory::CheckBoxParam(this->window_id, this->group, check_state);

				// �����¼�
				if (callback_down) {
					callback_down(window_id);
				}
			}
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
void UI_CheckBox::Update() {
	if (window_release) {
		return;
	}

	// ����״̬
	// ��ͼ��Դ����
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
	// �л���Դ����
	else if (button_style == CheckBoxStyle_ChangeOp_Once || button_style == CheckBoxStyle_ChangeOp_Two) {
		button_state = 1;
		if (check_state == 1) {
			button_state = 2;
		}
	}

	// ״̬����
	if (!list_image.empty()) {
		if (button_style == CheckBoxStyle_OneOnce || button_style == CheckBoxStyle_ChangeOp_Once) {
			auto& _image = list_image[0];
			int resLine = (button_style == CheckBoxStyle_OneOnce) ? 4 : 2;

			// ����ü�
			auto image = _image->GetImage();

			// ����
			_image->Update();
		}
		else if (button_style == CheckBoxStyle_OneFour || button_style == CheckBoxStyle_ChangeOp_Two) {
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
void UI_CheckBox::Draw() {
	if (window_release) {
		return;
	}

	// ����ͼ��
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

	// �ı�
	if (_text) {
		_text->Draw();
	}

}

// ��������
void UI_CheckBox::SetRect(int x, int y, int width, int height) {
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
void UI_CheckBox::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}

// ���õ�ѡ
void UI_CheckBox::SetCheckBoxType(int _type) {
	check_state = _type;
}

// ����������
void UI_CheckBox::SetGroupId(int _id) {
	this->group = _id;
}

// ��ȡ��ѡ״̬
bool UI_CheckBox::GetCheckState() {
	return check_state == 1;
}

// ���ûص�
void UI_CheckBox::Event_Hover(std::function<void(int Id)> _hover) {
	// this->callback_hover = _hover;
	// ��ѡ�� - ��������ǰ�¼�
}

// ���ûص� - ����
void UI_CheckBox::Event_Down(std::function<void(int Id)> _down) {
	this->callback_down = _down;
}

// ���ûص� - �ſ�
void UI_CheckBox::Event_Up(std::function<void(int Id)> _up) {
	// this->callback_up = _up;
	// ��ѡ�� - ��������ǰ�¼�
}

// ���ûص� - ���
void UI_CheckBox::Event_Click(std::function<void(int Id)> _click) {
	// this->callback_click = _click;
	// ��ѡ�� - ��������ǰ�¼�
}
