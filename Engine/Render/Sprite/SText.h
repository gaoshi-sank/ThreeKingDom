#ifndef _SText_h_
#define _SText_h_

#include "BaseSprite.h"


class SText : public Sprite {
private:
	// 文本
	std::string text;						// 文字
	wchar_t* render_text;					// 渲染用
	float font_size;						// 文字大小
	IDWriteTextFormat* text_format;			// 文字格式
	IDWriteTextLayout* text_layout;			// 文本布局 
	ID2D1SolidColorBrush* text_brash;		// 底子画刷 
	D2D1_COLOR_F text_color;				// 画刷颜色

	int max_fontlength;						// 可绘制文本长度
	int text_HorizontalStyle;				// 文本水平风格 - 1 默认居中
	int text_VerticalStyle;					// 文本垂直风格 - 1 默认居中
	int text_swrapping;						// 换行格式


public:
	// 构造
	SText();

	// 构造
	SText(const char* _text);

	// 析构
	~SText();

	// 更新
	virtual void Update();

	// 绘制文本
	virtual void Draw();

	// 绘制文本
	virtual void Draw(const std::string& render_text, D2D1_RECT_F other_rect);

	// 设置绘制区域
	virtual void SetRect(D2D1_RECT_F _rect);

	// 设置旋转
	virtual void SetRotate(float angle);

	// 获取图像
	virtual ID2D1Bitmap* GetImage();

	// 重设布局 
	// 水平格式: 居中
	// 垂直格式: 居中
	// 自动换行: 保持同一行 
	void ReSetLayout(int level_Style = 1, int vertical_Style = 0, int swrapping = 1);

	// 重设文本
	void ReSetText(const char* text = nullptr);

	// 重设字体大小 
	void ReSetFont(float font_size = 18.0f);

	// 重设颜色 
	void ReSetColor(D2D1_COLOR_F _color);


};



#endif // !_SText_h_