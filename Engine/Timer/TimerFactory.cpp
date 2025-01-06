#include "TimerFactory.h"

std::thread* TimerFactory::mainThread = nullptr;	// 线程句柄
int TimerFactory::thread_status = 0;				// 线程状态
std::vector<Timer*> TimerFactory::ListTimer;		// 计时器列表
std::mutex TimerFactory::lock_List;					// 锁 - 计时器列表
std::mutex TimerFactory::lock_thread;				// 锁 - 线程
std::condition_variable TimerFactory::cv_thread;	// 条件 - 线程

// 初始化时间工厂
void TimerFactory::InitTimerFactory() {
	// 建立线程
	if (!mainThread) {
		thread_status = 1;
		mainThread = new std::thread(ThreadLoop);
		mainThread->detach();
	}
}

// 停止计时器工厂
void TimerFactory::Release() {
	{
		thread_status = 0;
		std::unique_lock<std::mutex> lock(lock_thread);
		cv_thread.wait(lock, [&]() {
			return thread_status == 2;
		});
	}

	// 释放计时器
	std::vector<Timer*>::iterator it;
	for (it = ListTimer.begin(); it != ListTimer.end();it++) {
		if (*it) {
			(*it)->exit();
			delete (*it);
			(*it) = nullptr;
		}
	}
	ListTimer.clear();

}

// 创建计时器
// 回调函数，触发间隔，是否循环
Timer* TimerFactory::SetTimer(std::function<void(int* param)> callback_handle, float tiggerTimer, bool isLoop) {
	Timer* _timer = new Timer(callback_handle);
	if (_timer) {
		_timer->setLine(tiggerTimer);
		_timer->setLoop(isLoop);
		_timer->start();

		std::lock_guard<std::mutex> lock(lock_List);
		ListTimer.push_back(_timer);
	}
	return _timer;
}

// 线程运行
void TimerFactory::ThreadLoop() {

	LARGE_INTEGER mainTimer;
	
	while (thread_status) {
		QueryPerformanceCounter(&mainTimer);

		{
			// 声明开始
			std::lock_guard<std::mutex> lock(lock_List);

			// 删除
			std::vector<Timer*>::iterator it;
			for (it = ListTimer.begin(); it != ListTimer.end();) {
				bool iskeep = true;
				if (*it && (*it)->isrelease()) {
					auto del_node = (*it);
					delete del_node;
					del_node = nullptr;
					iskeep = false;
					it = ListTimer.erase(it);
				}
				if (iskeep) {
					it++;
				}
			}

			// 更新
			for (auto& node : ListTimer) {
				if (node) {
					node->update(mainTimer);
				}
			}
		}
	}
	{
		std::unique_lock<std::mutex> lock(lock_thread);
		thread_status = 2;
		cv_thread.notify_one();
	}
}