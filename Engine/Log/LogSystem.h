#ifndef _LogSystem_h_
#define _LogSystem_h_

#include "../EngineConfig.h"

// log��
class LogSystem {
private:
	// ����
	LogSystem();

	// ����
	~LogSystem();

	// ����ֵ
	std::thread* mainThread;				// �ֳ�
	int mainStatus;							// ״ֵ̬
	std::mutex lock_main;					// ��
	std::condition_variable cv_main;		// ����
	std::map<std::string, int> TagMapping;	// tagӳ��


public:
	// ��ʼ��logϵͳ
	static void InitLogSystem();

	// ֹͣlogϵͳ
	static void StopLogSystem();

	// ��ȡLog��������
	static void ReadLogSwitch();

private:
	// �����̴߳���
	void ThreadLoop();

	// �ȴ��߳̽���
	void WaittingThread();

	// ����tagֵ
	void SetTag(std::string tag, int value);
};




#endif // !_LogSystem_h_
