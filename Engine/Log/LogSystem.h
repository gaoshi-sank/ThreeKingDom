#ifndef _LogSystem_h_
#define _LogSystem_h_

#include "../EngineConfig.h"
#include "Mempool/MemPool.h"

// log��
class LogSystem {
private:
	// ����ֵ
	std::thread* mainThread;				// �߳�
	int mainStatus;							// ״ֵ̬
	std::mutex lock_main;					// ��
	std::condition_variable cv_main;		// ����
	std::map<std::string, int> TagMapping;	// tagӳ��
	std::queue<char*> bufferList;			// д��buffer����
	std::mutex lock_buffer;					// �� - buffer����
	int open_logsystem;						// ����ֵ

public:
	// ����
	// ѡ���Ƿ���
	LogSystem(bool Open = true);

	// ����
	~LogSystem();

	// ��ȡ���
	static std::shared_ptr<LogSystem> GetInstance();

	// ��ȡLog��������
	void ReadLogSwitch();

	// enque
	void Enque(char* buffer, int len);

private:
	// �����̴߳���
	void ThreadLoop();

	// �ȴ��߳̽���
	void WaittingThread();

	// ����tagֵ
	void SetTag(std::string tag, int value);
};

// д��log
void LogI(const char* format, ...);


#endif // !_LogSystem_h_
