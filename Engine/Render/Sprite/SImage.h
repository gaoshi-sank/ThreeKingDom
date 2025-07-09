#ifndef _SImage_h_
#define _SImage_h_

#include "BaseSprite.h"


class SImage : public Sprite {
private:
	// 图像
	ID2D1Bitmap* _image;	// 图像对象
	float opacity;			// 不透明度
	float angle;			// 旋转角度
	D2D1_RECT_F src_rect;	// 资源裁剪区

public:
	// 构造
	SImage();

	// 构造
	SImage(const char* filename);

	// 析构
	~SImage();

	// 更新
	virtual void Update();

	// 绘制图像
	virtual void Draw();

	// 绘制图像 - 外部提供图像资源
	virtual void Draw(ID2D1Bitmap* _image);

	// 设置绘制区域
	virtual void SetRect(D2D1_RECT_F _rect);

	// 设置旋转
	virtual void SetRotate(float angle);

	// 设置裁剪区域
	virtual void SetCrop(D2D1_RECT_F cropRect);

	// 获取图像
	virtual ID2D1Bitmap* GetImage();

	// 获取旋转
	virtual float GetRotate();

	// 获取裁剪区域
	virtual D2D1_RECT_F GetCrop();

	// 保存数据
	virtual void SaveToFile(const char* filename );

};

#endif // !_SImage_h_