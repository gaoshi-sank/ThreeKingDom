#ifndef _BaseSprite_h_
#define _BaseSprite_h_

#include "../Render.h"	// 渲染器

// 声明
const int limit_length = 1024;

// 精灵类
class Sprite {
public:
	bool visiable;				// 可见性					
	D2D1_RECT_F draw_rect;		// 绘制区

public:
	// 构造
	Sprite() {
		visiable = true;
		draw_rect = D2D1::RectF();
	}

	// 析构
	virtual ~Sprite() {

	}

	// 更新
	virtual void Update() = 0;

	// 绘制
	virtual void Draw() = 0;

	// 设置绘制区域
	virtual void SetRect(D2D1_RECT_F _rect) = 0;

	// 设置旋转
	virtual void SetRotate(float angle) = 0;
	
	// 获取图像
	virtual ID2D1Bitmap* GetImage() = 0;

	// 获取区域
	virtual D2D1_RECT_F GetRect() { return this->draw_rect; }

};

#endif // !_BaseSprite_h_
