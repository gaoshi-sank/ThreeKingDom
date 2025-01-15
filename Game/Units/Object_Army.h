#ifndef _Object_Amry_h_
#define _Object_Amry_h_

#include "Image/Image_Army.h"
#include "Object_Base.h"

class Object_Army : public Object_Base {
private:
	std::shared_ptr<Image_Army> image;



public:
	// 构造
	Object_Army();

	// 析构
	~Object_Army();

	// 创建
	void Create(int key);

	// 创建部队
	void CreateAmry(int x, int y);

	// 设置面向方向
	void SetFace(int face);

	// 更新
	void Update();

	// 绘制
	void Draw();
};


#endif // !_Object_Amry_h_
