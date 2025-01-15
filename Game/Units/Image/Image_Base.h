#ifndef _Image_Base_h_
#define _Image_Base_h_

#include "../../Datas/DataProvider.h"
#include "../../../Engine/Render/Sprite/Animation.h"
#include "../../../Engine/Render/Sprite/SImage.h"

class Image_Base {
public:
	unsigned int image_id;

	// 构造
	Image_Base();

	// 析构
	~Image_Base();

	// 初始化
	virtual void Create(int key) = 0;

	// 更新
	virtual void Update() = 0;

	// 绘制
	virtual void Draw() = 0;
};


#endif // !_Image_Base_h_
