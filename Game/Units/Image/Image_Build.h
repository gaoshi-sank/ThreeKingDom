#ifndef _Image_Build_h_
#define _Image_Build_h_

#include "../../../Engine/Render/Sprite/Animation.h"
#include "Image_Base.h"

class Image_Build : public Image_Base {
private:
	std::vector<std::shared_ptr<SImage>> imageList;
	int x, y, width, height;
	int buildLevel;			// 建筑等级
	int index_back;			// 背景索引
	int index_front;		// 前景索引
	int index_lvlup;		// 内饰索引


public:
	// 构造
	Image_Build();

	// 析构
	~Image_Build();

	// 初始化
	virtual void Create(int key);

	// 初始化
	virtual void Create(int key, int x, int y, int width, int height);

	// 设置位置
	virtual void SetLocation(int x,int y);

	// 设置大小
	virtual void SetSize(int width, int height);

	// 更新
	virtual void Update();

	// 绘制
	virtual void Draw();

private:
	// 设置索引
	void SetBuildIndex(int level);

};


#endif // !_Image_Build_h_
