#ifndef _LogSystem_h_
#define _LogSystem_h_

#include "../EngineConfig.h"

// log类
class LogSystem {
private:
	// 构造
	LogSystem();

	// 析构
	~LogSystem();

	// 属性值
	std::thread* mainThread;				// 现成
	int mainStatus;							// 状态值
	std::mutex lock_main;					// 锁
	std::condition_variable cv_main;		// 条件
	std::map<std::string, int> TagMapping;	// tag映射


public:
	// 初始化log系统
	static void InitLogSystem();

	// 停止log系统
	static void StopLogSystem();

	// 读取Log开关配置
	static void ReadLogSwitch();

private:
	// 独立线程处理
	void ThreadLoop();

	// 等待线程结束
	void WaittingThread();

	// 设置tag值
	void SetTag(std::string tag, int value);
};




#endif // !_LogSystem_h_
