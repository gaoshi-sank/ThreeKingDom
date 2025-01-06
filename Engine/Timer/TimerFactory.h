#ifndef _TimerFactory_h_
#define _TimerFactory_h_

#include "Timer.h"

// 时间管理类
class TimerFactory {
private:
	static std::thread* mainThread;			// 主线程句柄
	static int thread_status;				// 主线程状态
	static std::vector<Timer*> ListTimer;	// 计时器列表
	static std::mutex lock_List;			// 列表 - 锁
	static std::mutex lock_thread;				// 锁 - 线程
	static std::condition_variable cv_thread;	// 条件 - 线程

public:
	// 初始化计时器工厂
	static void InitTimerFactory();

	// 停止计时器工厂
	static void Release();

	// 创建计时器
	// 回调函数，触发间隔，是否循环
	static Timer* SetTimer(std::function<void(int*)> callback_handle, float tiggerTimer, bool isLoop);



private:
	// 线程运行
	static void ThreadLoop();


};

#endif //!_TimerFactory_h_