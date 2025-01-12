#ifndef _Object_Build_h_
#define _Object_Build_h_

#include "Image/Image_Build.h"
#include "Object_Base.h"

class Object_Build : public Object_Base {
private:
	std::shared_ptr<Image_Build> image;



public:
	// 构造
	Object_Build();

	// 析构
	~Object_Build();

	// 创建
	void Create(int key);

	// 创建建筑
	void CreateBuild(int x, int y);

	// 更新
	void Update();

	// 绘制
	void Draw();


};


#endif // !_Object_Build_h_
