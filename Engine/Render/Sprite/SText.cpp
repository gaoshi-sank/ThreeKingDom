#include "SText.h"
#include "SpriteHelper.h"
#include "../RenderFactory.h"
#include "../Direct2D/Render_Direct2d.h"

// 构造
SText::SText() {
	// 文本属性
	text = "";					// 文字
	render_text = nullptr;		// 渲染用文字
	font_size = 18.0f;			// 文字大小
	text_format = nullptr;		// 文字格式
	text_layout = nullptr;		// 文本布局 
	text_brash = nullptr;		// 底子画刷 
	memset(text_color, 0, sizeof(int) * 3);	// 画刷颜色
	max_fontlength = 1024;		// 可绘制文本长度
	text_HorizontalStyle = 1;	// 文本水平风格
	text_VerticalStyle = 1;		// 文本垂直风格
	text_swrapping = 0;			// 换行格式

	// 创建可用对象
	ReSetFont(font_size);
	ReSetColor(text_color[0], text_color[1], text_color[2]);
}

// 构造
SText::SText(const char* _text) : SText() {
	// 重新设置文本
	ReSetText(_text);

	// 重设文本布局
	ReSetLayout();
}

// 析构
SText::~SText() {
	// 渲染用文本
	if (render_text) {
		delete[] render_text;
		render_text = nullptr;
	}

	// 文字格式-布局-画刷
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

// 更新
void SText::Update() {

}

// 绘制图像
void SText::Draw() {
	if (render_text && visiable) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderText(render_text, draw_x, draw_y, draw_width, draw_height, text_layout, text_brash);
		}
	}
}

// 设置绘制位置
void SText::SetLocaiton(int x, int y) {
	this->draw_x = x;
	this->draw_y = y;
}

// 设置绘制大小
void SText::SetSize(int w, int h) {
	this->draw_width = w;
	this->draw_height = h;
}

// 设置旋转 
// 暂未实装
void SText::SetRotate(float angle) {

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
	}
}

// 重设字体大小
void SText::ReSetFont(float _font_size) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		render->ReleaseObject(text_format);
		text_format = render->CreateTextFormat(_font_size);
	}
}

// 重设颜色 
void SText::ReSetColor(int red, int green, int blue) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render) {
		render->ReleaseObject(text_brash);
		text_brash = render->CreateBrush(red, green, blue);
	}
}


