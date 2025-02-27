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
	void CreateByMul(const char* filename, int x, int y, int width, int height, int cropx = 0, int cropy = 0, int cropwidth = 0, int cropheight = 0);

	// 创建
	void CreateByOne(const char* filename, int x, int y, int width, int height, int cropwidth, int cropheight);

	// 创建
	void AddSprite(SImage* _newsprite);

	// 设置播放帧率
	// 帧率 = 1 ~ 120
	void SetPlaySpeed(int number);

	// 更新
	virtual void Update() override;

	// 绘制
	virtual void Draw() override;

	// 设置绘制位置
	virtual void SetLocation(int x, int y) override;

	// 设置绘制大小
	virtual void SetSize(int w, int h) override;

	// 设置旋转
	// 暂未实装
	virtual void SetRotate(float angle) override;

	// 获取绘制位置
	virtual void GetLocation(int& x, int& y);

	// 获取绘制大小
	virtual void GetSize(int& w, int& h);

	// 获取旋转
	// 暂未实装
	virtual void GetRotate(float& angle);

private:
	// 计时器回调
	void CallbackFunction();


};

#endif //!_Animation_h_