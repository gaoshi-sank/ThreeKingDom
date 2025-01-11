#ifndef _BaseSprite_h_
#define _BaseSprite_h_

#include "../Render.h"	// 渲染器

// 声明
const int limit_length = 1024;

// 精灵类
class Sprite {
public:
	bool visiable;					// 可见性					
	int draw_x, draw_y, 
		draw_width, draw_height;	// 绘制区

public:
	// 构造
	Sprite() {
		visiable = true;
		draw_x = draw_y = draw_width = draw_height = 0;
	}

	// 析构
	virtual ~Sprite() {

	}

	// 更新
	virtual void Update() = 0;

	// 绘制
	// 图像、图形、线条、文本
	virtual void Draw() = 0;

	// 设置绘制位置
	virtual void SetLocation(int x, int y) = 0;

	// 设置绘制大小
	virtual void SetSize(int w, int h) = 0;

	// 设置旋转
	virtual void SetRotate(float angle) = 0;

	// 获取绘制位置
	virtual void GetLocation(int& x, int& y) = 0;

	// 获取绘制大小
	virtual void GetSize(int& w, int& h) = 0;

	// 获取旋转
	virtual void GetRotate(float& angle) = 0;

};

#endif // !_BaseSprite_h_
