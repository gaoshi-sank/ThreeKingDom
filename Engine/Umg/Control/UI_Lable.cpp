#include "UI_Lable.h"

// ����
UI_Lable::UI_Lable() {
	_image = nullptr;
	_text = nullptr;
	window_style = UIStyle_Lable;
}

// ����
UI_Lable::~UI_Lable() {
	// ͼ��
	if (_image) {
		delete _image;
		_image = nullptr;
	}

	// �ı�
	if (_text) {
		delete _text;
		_text = nullptr;
	}
}

void UI_Lable::PreRelease(){
	window_release = true;
};

// ����
bool UI_Lable::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// ����ͼ�� 
// ������λ�úʹ�С
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

// ���Ӿ�̬�ı�
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

// �¼�����
void UI_Lable::CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams) {
	// ��ǩUI������
}


// ����
void UI_Lable::Update() {
	if (window_release) {
		return;
	}

	// ͼ��
	if (_image) {
		_image->Update();
	}

	// �ı�
	if (_text) {
		_text->Update();
	}

}

// ����
void UI_Lable::Draw() {
	if (window_release) {
		return;
	}

	// ͼ��
	if (_image) {
		_image->Draw();
	}

	// �ı�
	if (_text) {
		_text->Draw();
	}

}

// ��������
void UI_Lable::SetRect(int x, int y, int width, int height) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;
	this->window_width = width;
	this->window_height = height;

	// ͼ��
	if (_image) {
		_image->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
	}

	// �ı�
	if (_text) {
		_text->SetRect(D2D1::RectF((float)window_x, (float)window_y, (float)window_x + window_width, (float)window_y + window_height));
	}
}

// ���ÿɼ���
void UI_Lable::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}
