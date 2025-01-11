#ifndef _SImage_h_
#define _SImage_h_

#include "BaseSprite.h"


class SImage : public Sprite {
private:
	// 图像
	void* _image;				// 图像对象
	float opacity;				// 不透明度
	float angle;				// 旋转角度
	int src_x, src_y,
		src_width, src_height;	// 资源裁剪区

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

	// 设置绘制位置
	virtual void SetLocation(int x, int y);

	// 设置绘制大小
	virtual void SetSize(int w, int h);

	// 设置旋转 
	virtual void SetRotate(float angle);

	// 设置裁剪
	virtual void SetCrop(int x, int y, int width, int height);

	// 获取图像大小
	virtual bool GetImageSize(int& width, int& height);

	// 获取绘制位置
	virtual void GetLocation(int& x, int& y);

	// 获取绘制大小
	virtual void GetSize(int& w, int& h);

	// 获取旋转
	virtual void GetRotate(float& angle);
};

#endif // !_SImage_h_