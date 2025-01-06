#ifndef _TimerFactory_h_
#define _TimerFactory_h_

#include "Timer.h"

// ʱ�������
class TimerFactory {
private:
	static std::thread* mainThread;			// ���߳̾��
	static int thread_status;				// ���߳�״̬
	static std::vector<Timer*> ListTimer;	// ��ʱ���б�
	static std::mutex lock_List;			// �б� - ��
	static std::mutex lock_thread;				// �� - �߳�
	static std::condition_variable cv_thread;	// ���� - �߳�

public:
	// ��ʼ����ʱ������
	static void InitTimerFactory();

	// ֹͣ��ʱ������
	static void Release();

	// ������ʱ��
	// �ص�����������������Ƿ�ѭ��
	static Timer* SetTimer(std::function<void(int*)> callback_handle, float tiggerTimer, bool isLoop);



private:
	// �߳�����
	static void ThreadLoop();


};

#endif //!_TimerFactory_h_