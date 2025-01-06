#include "SText.h"
#include "SpriteHelper.h"
#include "../RenderFactory.h"
#include "../Direct2D/Render_Direct2d.h"

// ����
SText::SText() {
	// �ı�����
	text = "";					// ����
	render_text = nullptr;		// ��Ⱦ������
	font_size = 18.0f;			// ���ִ�С
	text_format = nullptr;		// ���ָ�ʽ
	text_layout = nullptr;		// �ı����� 
	text_brash = nullptr;		// ���ӻ�ˢ 
	memset(text_color, 0, sizeof(int) * 3);	// ��ˢ��ɫ
	max_fontlength = 1024;		// �ɻ����ı�����
	text_HorizontalStyle = 1;	// �ı�ˮƽ���
	text_VerticalStyle = 1;		// �ı���ֱ���
	text_swrapping = 0;			// ���и�ʽ

	// �������ö���
	ReSetFont(font_size);
	ReSetColor(text_color[0], text_color[1], text_color[2]);
}

// ����
SText::SText(const char* _text) : SText() {
	// ���������ı�
	ReSetText(_text);

	// �����ı�����
	ReSetLayout();
}

// ����
SText::~SText() {
	// ��Ⱦ���ı�
	if (render_text) {
		delete[] render_text;
		render_text = nullptr;
	}

	// ���ָ�ʽ-����-��ˢ
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		render->ReleaseObject(text_format);
		render->ReleaseObject(text_layout);
		render->ReleaseObject(text_brash);
	}

	text_format = nullptr;
	text_layout = nullptr;
	text_brash = nullptr;
}

// ����
void SText::Update() {

}

// ����ͼ��
void SText::Draw() {
	if (render_text && visiable) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderText(render_text, draw_x, draw_y, draw_width, draw_height, text_layout, text_brash);
		}
	}
}

// ���û���λ��
void SText::SetLocaiton(int x, int y) {
	this->draw_x = x;
	this->draw_y = y;
}

// ���û��ƴ�С
void SText::SetSize(int w, int h) {
	this->draw_width = w;
	this->draw_height = h;
}

// ������ת 
// ��δʵװ
void SText::SetRotate(float angle) {

}

// ���貼�� 
void SText::ReSetLayout(int horizontal_Style, int vertical_Style, int swrapping) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		// ���´���ʵ������
		if (!text_layout) {
			text_layout = render->CreateTextLayout(this->render_text, this->text_format);
		}
		
		// �����ı���ʽ
		render->SetTextStyle(text_layout, horizontal_Style, vertical_Style, swrapping);
	}
}

// �����ı�
void SText::ReSetText(const char* _text) {
	if (_text) {
		// �޸��ı�
		this->text.clear();
		this->text = _text;

		// �ֽ�ת��
		// ��������
		if (this->render_text) {
			delete[] this->render_text;
			this->render_text = nullptr;
		}

		size_t loopnum = text.size() / limit_length;
		this->render_text = new wchar_t[limit_length * (loopnum + 1)];
		memset(this->render_text, '\0', sizeof(wchar_t) * (limit_length * (loopnum + 1)));
		CharToWChar(this->text.c_str(), this->render_text);
	}
}

// ���������С
void SText::ReSetFont(float _font_size) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		render->ReleaseObject(text_format);
		text_format = render->CreateTextFormat(_font_size);
	}
}

// ������ɫ 
void SText::ReSetColor(int red, int green, int blue) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		render->ReleaseObject(text_brash);
		text_brash = render->CreateBrush(red, green, blue);
	}
}


