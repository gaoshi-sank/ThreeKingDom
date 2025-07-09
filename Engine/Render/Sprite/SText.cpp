#include "SText.h"
#include "../../EngineHelper.h"
#include "../RenderFactory.h"

// 构造
SText::SText() {
	// 文本属性
	text = "";							// 文字
	render_text = nullptr;				// 渲染用文字
	font_size = 18.0f;					// 文字大小
	text_format = nullptr;				// 文字格式
	text_layout = nullptr;				// 文本布局 
	text_brash = nullptr;				// 底子画刷 
	max_fontlength = 1024;				// 可绘制文本长度
	text_HorizontalStyle = 1;			// 文本水平风格
	text_VerticalStyle = 1;				// 文本垂直风格
	text_swrapping = 0;					// 换行格式
	text_color = D2D1::ColorF(0, 0, 0);	// 画刷颜色

	// 创建可用对象
	ReSetFont(font_size);
	ReSetColor(text_color);
}

// 构造
SText::SText(const char* _text) : SText() {
	ReSetText(_text);
}

// 析构
SText::~SText() {
	// 渲染用文本
	if (render_text) {
		delete[] render_text;
		render_text = nullptr;
	}

	// 文字格式-布局-画刷
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

// 更新
void SText::Update() {

}

// 绘制文本
void SText::Draw() {
	if (render_text && visiable) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderText(render_text, draw_rect, text_layout, text_brash);
		}
	}
}

// 绘制文本
void SText::Draw(const std::string& draw_text, D2D1_RECT_F other_rect) {
	if (!draw_text.empty() && visiable) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			// 切换格式
			size_t loopnum = draw_text.size() / limit_length;
			auto other_text = new wchar_t[limit_length * (loopnum + 1)];
			if (other_text) {
				memset(other_text, '\0', sizeof(wchar_t) * (limit_length * (loopnum + 1)));
				CharToWChar(draw_text.c_str(), other_text);

				// 渲染
				render->RenderText(other_text, other_rect, text_layout, text_brash);
			}
		}
	}
}

// 设置绘制区域
void SText::SetRect(D2D1_RECT_F _rect) {
	this->draw_rect = _rect;
}

// 设置旋转
void SText::SetRotate(float angle) {
	// 不实例化
}

// 获取图像
ID2D1Bitmap* SText::GetImage() {
	return nullptr;
}

// 重设布局 
void SText::ReSetLayout(int horizontal_Style, int vertical_Style, int swrapping) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		// 重新创建实例对象
		if (!text_layout) {
			text_layout = render->CreateTextLayout(this->render_text, this->text_format);
		}
		
		// 设置文本格式
		render->SetTextStyle(text_layout, horizontal_Style, vertical_Style, swrapping);
	}
}

// 重设文本
void SText::ReSetText(const char* _text) {
	if (_text) {
		// 修改文本
		this->text.clear();
		this->text = _text;

		// 字节转换
		// 重新申请
		if (this->render_text) {
			delete[] this->render_text;
			this->render_text = nullptr;
		}
		size_t loopnum = text.size() / limit_length;
		this->render_text = new wchar_t[limit_length * (loopnum + 1)];
		memset(this->render_text, '\0', sizeof(wchar_t) * (limit_length * (loopnum + 1)));
		CharToWChar(this->text.c_str(), this->render_text);
		
		// 重设文本布局
		ReSetLayout();
	}
}

// 重设字体大小
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

// 重设颜色 
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


