#ifndef _SText_h_
#define _SText_h_

#include "BaseSprite.h"


class SText : public Sprite {
private:
	// 文本
	std::string text;			// 文字
	wchar_t* render_text;		// 渲染用
	float font_size;			// 文字大小
	void* text_format;			// 文字格式
	void* text_layout;			// 文本布局 
	void* text_brash;			// 底子画刷 
	int text_color[3];			// 画刷颜色
	int max_fontlength;			// 可绘制文本长度
	int text_HorizontalStyle;	// 文本水平风格 - 1 默认居中
	int text_VerticalStyle;		// 文本垂直风格 - 1 默认居中
	int text_swrapping;			// 换行格式


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
	virtual void Draw(const std::string& render_text, int dx, int dy, int dw, int dh);

	// 设置绘制位置
	virtual void SetLocation(int x, int y);

	// 设置绘制大小
	virtual void SetSize(int w, int h);

	// 设置旋转 
	// 暂未实装
	virtual void SetRotate(float angle);

	// 获取绘制位置
	virtual void GetLocation(int& x, int& y);

	// 获取绘制大小
	virtual void GetSize(int& w, int& h);

	// 获取旋转
	// 暂未实装
	virtual void GetRotate(float& angle);

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
	void ReSetColor(int red, int green, int blue);


};



#endif // !_SText_h_