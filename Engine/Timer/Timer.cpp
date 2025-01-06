#include "Timer.h"

static unsigned int timers_id = 0;

// 构造
Timer::Timer() {
	timer_id = ++timers_id;					// 编号
	option_timer = 0.0f;					// 回调间隔
	option_loop = true;						// 默认循环
	timer_state = TimerState_init;			// 初始化
	trigger_function = nullptr;				// 回调函数

	QueryPerformanceFrequency(&frequency);	// cpu频率
	QueryPerformanceCounter(&timer_start);	// 计时开始
	QueryPerformanceCounter(&timer_end);	// 计时结束
}

// 构造
Timer::Timer(std::function<void(int*)> callback_handle) : Timer() {
	this->trigger_function = callback_handle;
}

// 析构
Timer::~Timer() {

}

// 设置计时间隔
void Timer::setLine(float timenumber) {
	this->option_timer = timenumber;
}

// 设置是否循环
void Timer::setLoop(bool option) {
	this->option_loop = option;
}

// 单独计时
void Timer::getStart() {
	QueryPerformanceCounter(&timer_start);
	QueryPerformanceCounter(&timer_end);
}

// 获取逝去时间
double Timer::getOvertime() {
	if (timer_state != TimerState_stop) {
		QueryPerformanceCounter(&timer_start);
		double elapsedTime = static_cast<double>(timer_start.QuadPart - timer_end.QuadPart) / (frequency.QuadPart * 1.0 / 1000);
		return elapsedTime;
	}
	return 0.0f;
}

// 开始计时 
void Timer::start() {
	timer_state = TimerState_start;
	QueryPerformanceCounter(&timer_start);
	QueryPerformanceCounter(&timer_end);
}

// 暂停计时
void Timer::pause() {
	timer_state = TimerState_pause;
	QueryPerformanceCounter(&timer_start);
	QueryPerformanceCounter(&timer_end);
}

// 结束计时
void Timer::exit() {
	timer_state = TimerState_stop;
	timer_id = 0x00;
}

// 判定释放
bool Timer::isrelease() {
	return (timer_state == TimerState_stop);
}

// 更新 
void Timer::update(LARGE_INTEGER now_timer) {
	timer_start = now_timer;

	// 开始
	if (timer_state == TimerState_start) {
		double elapsedTime = static_cast<double>(timer_start.QuadPart - timer_end.QuadPart) / (frequency.QuadPart * 1.0 / 1000);
		if (abs(elapsedTime) >= 0.001f && abs(elapsedTime) >= option_timer) {
			timer_end = timer_start;
			// 计时器到期
			if (trigger_function) {
				trigger_function(nullptr);
			}

			// 循环触发
			if (!option_loop) {
				this->exit();
			}
		}
	}
	// 暂停
	else if (timer_state == TimerState_pause) {
		timer_end = timer_start;
	}
}