#include "TimerFactory.h"

std::thread* TimerFactory::mainThread = nullptr;	// �߳̾��
int TimerFactory::thread_status = 0;				// �߳�״̬
std::vector<Timer*> TimerFactory::ListTimer;		// ��ʱ���б�
std::mutex TimerFactory::lock_List;					// �� - ��ʱ���б�
std::mutex TimerFactory::lock_thread;				// �� - �߳�
std::condition_variable TimerFactory::cv_thread;	// ���� - �߳�

// ��ʼ��ʱ�乤��
void TimerFactory::InitTimerFactory() {
	// �����߳�
	if (!mainThread) {
		thread_status = 1;
		mainThread = new std::thread(ThreadLoop);
		mainThread->detach();
	}
}

// ֹͣ��ʱ������
void TimerFactory::Release() {
	{
		thread_status = 0;
		std::unique_lock<std::mutex> lock(lock_thread);
		cv_thread.wait(lock, [&]() {
			return thread_status == 2;
		});
	}

	// �ͷż�ʱ��
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

// ������ʱ��
// �ص�����������������Ƿ�ѭ��
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

// �߳�����
void TimerFactory::ThreadLoop() {

	LARGE_INTEGER mainTimer;
	
	while (thread_status) {
		QueryPerformanceCounter(&mainTimer);

		{
			// ������ʼ
			std::lock_guard<std::mutex> lock(lock_List);

			// ɾ��
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

			// ����
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