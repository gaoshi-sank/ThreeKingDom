#ifndef _Timer_h_
#define _Timer_h_

#include <Windows.h>
#include "../EngineConfig.h"

// �Զ���ʱ����
class Timer {
private:
	unsigned int timer_id;		// ��ʱ�����
	LARGE_INTEGER frequency;	// ��ʱƵ��
	LARGE_INTEGER timer_start;
	LARGE_INTEGER timer_end;	// ��ʱ��
	bool option_loop;			// ѭ������
	float option_timer;			// ��ʱʱ��
	int timer_state;			// ��ʱ״̬

	// �ص�����
	std::function<void(int*)> trigger_function;

public:
	enum TimerState {
		TimerState_init = 1,
		TimerState_start,
		TimerState_pause,
		TimerState_stop,
	};

public:
	// ����
	Timer();

	// ����
	Timer(std::function<void(int*)> callback_handle);

	// ����
	~Timer();

	// ���ü�ʱ���
	void setLine(float timenumber); 

	// �����Ƿ�ѭ��
	void setLoop(bool option);

	// ������ʱ
	void getStart();

	// ��ȡ��ȥʱ��
	double getOvertime();

	// ��ʼ��ʱ 
	void start();

	// ��ͣ��ʱ
	void pause();

	// ������ʱ
	void exit();

	// �ж��ͷ�
	bool isrelease();

	// ���� 
	void update(LARGE_INTEGER now_timer);

};

#endif //!_Timer_h_