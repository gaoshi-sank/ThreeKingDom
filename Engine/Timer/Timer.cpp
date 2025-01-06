#include "Timer.h"

static unsigned int timers_id = 0;

// ����
Timer::Timer() {
	timer_id = ++timers_id;					// ���
	option_timer = 0.0f;					// �ص����
	option_loop = true;						// Ĭ��ѭ��
	timer_state = TimerState_init;			// ��ʼ��
	trigger_function = nullptr;				// �ص�����

	QueryPerformanceFrequency(&frequency);	// cpuƵ��
	QueryPerformanceCounter(&timer_start);	// ��ʱ��ʼ
	QueryPerformanceCounter(&timer_end);	// ��ʱ����
}

// ����
Timer::Timer(std::function<void(int*)> callback_handle) : Timer() {
	this->trigger_function = callback_handle;
}

// ����
Timer::~Timer() {

}

// ���ü�ʱ���
void Timer::setLine(float timenumber) {
	this->option_timer = timenumber;
}

// �����Ƿ�ѭ��
void Timer::setLoop(bool option) {
	this->option_loop = option;
}

// ������ʱ
void Timer::getStart() {
	QueryPerformanceCounter(&timer_start);
	QueryPerformanceCounter(&timer_end);
}

// ��ȡ��ȥʱ��
double Timer::getOvertime() {
	if (timer_state != TimerState_stop) {
		QueryPerformanceCounter(&timer_start);
		double elapsedTime = static_cast<double>(timer_start.QuadPart - timer_end.QuadPart) / (frequency.QuadPart * 1.0 / 1000);
		return elapsedTime;
	}
	return 0.0f;
}

// ��ʼ��ʱ 
void Timer::start() {
	timer_state = TimerState_start;
	QueryPerformanceCounter(&timer_start);
	QueryPerformanceCounter(&timer_end);
}

// ��ͣ��ʱ
void Timer::pause() {
	timer_state = TimerState_pause;
	QueryPerformanceCounter(&timer_start);
	QueryPerformanceCounter(&timer_end);
}

// ������ʱ
void Timer::exit() {
	timer_state = TimerState_stop;
	timer_id = 0x00;
}

// �ж��ͷ�
bool Timer::isrelease() {
	return (timer_state == TimerState_stop);
}

// ���� 
void Timer::update(LARGE_INTEGER now_timer) {
	timer_start = now_timer;

	// ��ʼ
	if (timer_state == TimerState_start) {
		double elapsedTime = static_cast<double>(timer_start.QuadPart - timer_end.QuadPart) / (frequency.QuadPart * 1.0 / 1000);
		if (abs(elapsedTime) >= 0.001f && abs(elapsedTime) >= option_timer) {
			timer_end = timer_start;
			// ��ʱ������
			if (trigger_function) {
				trigger_function(nullptr);
			}

			// ѭ������
			if (!option_loop) {
				this->exit();
			}
		}
	}
	// ��ͣ
	else if (timer_state == TimerState_pause) {
		timer_end = timer_start;
	}
}