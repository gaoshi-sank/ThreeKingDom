#ifndef _Timer_h_
#define _Timer_h_

#include <Windows.h>
#include "../EngineConfig.h"

// 自定义时间类
class Timer {
private:
	unsigned int timer_id;		// 计时器编号
	LARGE_INTEGER frequency;	// 计时频率
	LARGE_INTEGER timer_start;
	LARGE_INTEGER timer_end;	// 计时器
	bool option_loop;			// 循环开关
	float option_timer;			// 计时时间
	int timer_state;			// 计时状态

	// 回调函数
	std::function<void(int*)> trigger_function;

public:
	enum TimerState {
		TimerState_init = 1,
		TimerState_start,
		TimerState_pause,
		TimerState_stop,
	};

public:
	// 构造
	Timer();

	// 构造
	Timer(std::function<void(int*)> callback_handle);

	// 析构
	~Timer();

	// 设置计时间隔
	void setLine(float timenumber); 

	// 设置是否循环
	void setLoop(bool option);

	// 单独计时
	void getStart();

	// 获取逝去时间
	double getOvertime();

	// 开始计时 
	void start();

	// 暂停计时
	void pause();

	// 结束计时
	void exit();

	// 判定释放
	bool isrelease();

	// 更新 
	void update(LARGE_INTEGER now_timer);

};

#endif //!_Timer_h_