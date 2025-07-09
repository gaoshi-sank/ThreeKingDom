#ifndef _Animation_h_
#define _Animation_h_

#include "SImage.h"
#include "../../Timer/TimerFactory.h"

// 动画类
class Animation : public Sprite {
private:
	std::vector<SImage*> ListSprite;
	bool sameSprite;
	int showIndex;
	Timer* _timer;

public:
	// 构造
	Animation();

	// 析构
	virtual ~Animation();

	// 创建
	void CreateByMul(const char* filename, D2D1_RECT_F drawRect, D2D1_RECT_F cropRect);

	// 创建
	void CreateByOne(const char* filename, D2D1_RECT_F drawRect, D2D1_RECT_F cropRect);

	// 创建
	void AddSprite(SImage* _newsprite);

	// 设置播放帧率
	// 帧率 = 1 ~ 120
	void SetPlaySpeed(int number);

	// 更新
	virtual void Update();

	// 绘制
	virtual void Draw();

	// 设置绘制区域
	virtual void SetRect(D2D1_RECT_F _rect);

	// 设置旋转
	virtual void SetRotate(float angle);

	// 获取图像
	virtual ID2D1Bitmap* GetImage();

private:
	// 计时器回调
	void CallbackFunction();


};

#endif //!_Animation_h_