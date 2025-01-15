#ifndef _Object_Base_h_
#define _Object_Base_h_

#include "Image/Image_Base.h"

class Object_Base {
public:
	unsigned int object_id;

	// 构造
	Object_Base();

	// 析构
	~Object_Base();

	// 初始化
	virtual void Create(int key) = 0;

	// 更新
	virtual void Update() = 0;

	// 绘制
	virtual void Draw() = 0;
};



#endif // !_Object_Base_h_
