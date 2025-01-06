#ifndef _Animation_h_
#define _Animation_h_

#include "SImage.h"
#include "../../Timer/TimerFactory.h"

// 动画类
class Animation {
private:
	std::vector<SImage*> ListSprite;
	int showIndex;
	Timer* _timer;

public:
	// 构造
	Animation();

	// 析构
	~Animation();

	// 创建
	void AddSprite(const char* filename, int x, int y, int width, int height, int cropx, int cropy, int cropwidth, int cropheight);

	// 创建
	void AddSprite(SImage* _newsprite);

	// 设置播放帧率
	// 帧率 = 1 ~ 120
	void SetPlaySpeed(int number);

	// 更新
	void Update();

	// 绘制
	void Draw();

private:
	// 计时器回调
	void CallbackFunction();


};

#endif //!_Animation_h_