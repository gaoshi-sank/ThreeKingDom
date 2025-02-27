/*
* 动态图
*/
#ifndef _UI_GIF_H_
#define _UI_GIF_H_


#include "UI_Lable.h"
#include "../../../Engine/Render/Sprite/Animation.h"

enum GIFSTYLE {
	GIFSTYLE_NONE = 0,
	GIFSTYLE_MUL,
	GIFSTYLE_SINGLE,
};

// 静态图 
class UI_GIF : public UI_Lable {
private:
	Animation* _gif;	// 直接采用动画设置

public:
	// 构造
	UI_GIF();

	// 析构
	~UI_GIF();

	// 预释放
	virtual void PreRelease();

	// 创建
	virtual bool Create();

	// 创建单个图资源的GIF
	virtual bool Create(const std::string& filename, int rect_x, int rect_y, int rect_width, int rect_height, int cropWidth, int cropHeight, int speed);

	// 创建多个图资源的GIF
	virtual bool Create(std::vector<std::string> fileLists, int rect_x, int rect_y, int rect_width, int rect_height, int speed);

	// 事件驱动
	virtual void CheckEvent(unsigned int* param);

	// 更新 
	virtual void Update();

	// 绘制 
	virtual void Draw();

	// 设置位置
	virtual void SetLocation(int x, int y);

	// 设置大小
	virtual void SetSize(int w, int h);

	// 设置可见性
	virtual void SetVisiable(bool visible = true);
};


#endif // !_UI_GIF_H_