#ifndef _Image_Army_h_
#define _Image_Army_h_


#include "Image_Base.h"

class Image_Army : public Image_Base {
private:
	std::map<int, std::shared_ptr<Animation>> face_mapping;
	int face_Index;
	int x, y, width, height;

public:
	// 构造
	Image_Army();

	// 析构
	~Image_Army();

	// 初始化
	virtual void Create(int key);

	// 初始化
	virtual void Create(int key, int x, int y, int width, int height);

	// 设置位置
	virtual void SetLocation(int x,int y);

	// 设置大小
	virtual void SetSize(int width, int height);

	// 设置朝向
	virtual void SetFace(int face);

	// 更新
	virtual void Update();

	// 绘制
	virtual void Draw();


};


#endif // !_Image_Army_h_
