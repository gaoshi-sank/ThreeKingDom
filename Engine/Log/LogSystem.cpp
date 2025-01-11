#include "LogSystem.h"
#include "../FileControl/FileControl.h"

// 静态值
static LogSystem* g_log = nullptr;
static std::string debugConfig = "debugConfig.txt";		// debug配置
static std::string logFile = "logFile.txt";				// log输出文件

// 构造
LogSystem::LogSystem() {

	// 线程
	mainStatus = 1;
	mainThread = new std::thread(&LogSystem::ThreadLoop, this);

}

// 析构
LogSystem::~LogSystem() {

}


// 初始化log系统
void LogSystem::InitLogSystem() {
	if (!g_log) {
		g_log = new LogSystem();
	}
}

// 停止log系统
void LogSystem::StopLogSystem() {
	if (g_log) {
		g_log->WaittingThread();
		delete g_log;
		g_log = nullptr;
	}
}

// 读取Log开关配置
void LogSystem::ReadLogSwitch() {
	FILE* fp = fopen(debugConfig.c_str(), "r");
	if (fp && g_log) {
		while (1) {
			std::vector<StringMap> result;
			auto ret = FileControl::ReadJson(result, fp);
			if (ret == 2) {
				for (auto& key_value : result) {
					auto& key = key_value.key;
					auto& value = key_value.value;
					g_log->SetTag(key, std::atoi(value.c_str()));
				}
			}
			else {
				break;
			}
		}
		fclose(fp);
	}
	
}

// 独立线程处理
void LogSystem::ThreadLoop() {
	// 循环处理log消息
	while (mainStatus) {
		


	}
	{
		std::unique_lock<std::mutex> lock(lock_main);
		mainStatus = 2;
		cv_main.notify_one();
	}
}

// 等待线程结束
void LogSystem::WaittingThread() {
	{
		mainStatus = 0;
		std::unique_lock<std::mutex> lock(lock_main);
		cv_main.wait(lock, [&]() {
			return mainStatus == 2;
		});
	}
}

// 设置tag值
void LogSystem::SetTag(std::string tag, int value) {
	TagMapping[tag] = value;
}