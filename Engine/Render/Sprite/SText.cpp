#include "SText.h"
#include "../../EngineHelper.h"
#include "../RenderFactory.h"

// ����
SText::SText() {
	// �ı�����
	text = "";							// ����
	render_text = nullptr;				// ��Ⱦ������
	font_size = 18.0f;					// ���ִ�С
	text_format = nullptr;				// ���ָ�ʽ
	text_layout = nullptr;				// �ı����� 
	text_brash = nullptr;				// ���ӻ�ˢ 
	max_fontlength = 1024;				// �ɻ����ı�����
	text_HorizontalStyle = 1;			// �ı�ˮƽ���
	text_VerticalStyle = 1;				// �ı���ֱ���
	text_swrapping = 0;					// ���и�ʽ
	text_color = D2D1::ColorF(0, 0, 0);	// ��ˢ��ɫ

	// �������ö���
	ReSetFont(font_size);
	ReSetColor(text_color);
}

// ����
SText::SText(const char* _text) : SText() {
	ReSetText(_text);
}

// ����
SText::~SText() {
	// ��Ⱦ���ı�
	if (render_text) {
		delete[] render_text;
		render_text = nullptr;
	}

	// ���ָ�ʽ-����-��ˢ
	if (text_format) {
		text_format->Release();
	}
	if (text_layout) {
		text_layout->Release();
	}
	if (text_brash) {
		text_brash->Release();
	}

	text_format = nullptr;
	text_layout = nullptr;
	text_brash = nullptr;
}

// ����
void SText::Update() {

}

// �����ı�
void SText::Draw() {
	if (render_text && visiable) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderText(render_text, draw_rect, text_layout, text_brash);
		}
	}
}

// �����ı�
void SText::Draw(const std::string& draw_text, D2D1_RECT_F other_rect) {
	if (!draw_text.empty() && visiable) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			// �л���ʽ
			size_t loopnum = draw_text.size() / limit_length;
			auto other_text = new wchar_t[limit_length * (loopnum + 1)];
			if (other_text) {
				memset(other_text, '\0', sizeof(wchar_t) * (limit_length * (loopnum + 1)));
				CharToWChar(draw_text.c_str(), other_text);

				// ��Ⱦ
				render->RenderText(other_text, other_rect, text_layout, text_brash);
			}
		}
	}
}

// ���û�������
void SText::SetRect(D2D1_RECT_F _rect) {
	this->draw_rect = _rect;
}

// ������ת
void SText::SetRotate(float angle) {
	// ��ʵ����
}

// ��ȡͼ��
ID2D1Bitmap* SText::GetImage() {
	return nullptr;
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
		
		// �����ı�����
		ReSetLayout();
	}
}

// ���������С
void SText::ReSetFont(float _font_size) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		if (text_format) {
			text_format->Release();
			text_format = nullptr;
		}
		text_format = render->CreateTextFormat(_font_size);
	}
}

// ������ɫ 
void SText::ReSetColor(D2D1_COLOR_F _color) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		if (text_brash) {
			text_brash->Release();
			text_brash = nullptr;
		}
		text_brash = render->CreateBrush(_color);
	}
}


