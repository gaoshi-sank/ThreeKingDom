/*
* 卡牌类 - 图像渲染部分
*/
#ifndef _Image_Card_h_
#define _Image_Card_h_

#include "Image_Base.h"

class Image_Card : public Image_Base {
public:
	// 构造
	Image_Card();

	// 析构
	~Image_Card();

	// 初始化
	virtual void Create(int key);

	// 更新
	virtual void Update();

	// 绘制
	virtual void Draw();
};


#endif // !_Image_Card_h_
