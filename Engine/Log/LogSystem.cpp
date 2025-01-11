#include "LogSystem.h"
#include "../FileControl/FileControl.h"

// ��ֵ̬
static LogSystem* g_log = nullptr;
static std::string debugConfig = "debugConfig.txt";		// debug����
static std::string logFile = "logFile.txt";				// log����ļ�

// ����
LogSystem::LogSystem() {

	// �߳�
	mainStatus = 1;
	mainThread = new std::thread(&LogSystem::ThreadLoop, this);

}

// ����
LogSystem::~LogSystem() {

}


// ��ʼ��logϵͳ
void LogSystem::InitLogSystem() {
	if (!g_log) {
		g_log = new LogSystem();
	}
}

// ֹͣlogϵͳ
void LogSystem::StopLogSystem() {
	if (g_log) {
		g_log->WaittingThread();
		delete g_log;
		g_log = nullptr;
	}
}

// ��ȡLog��������
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

// �����̴߳���
void LogSystem::ThreadLoop() {
	// ѭ������log��Ϣ
	while (mainStatus) {
		


	}
	{
		std::unique_lock<std::mutex> lock(lock_main);
		mainStatus = 2;
		cv_main.notify_one();
	}
}

// �ȴ��߳̽���
void LogSystem::WaittingThread() {
	{
		mainStatus = 0;
		std::unique_lock<std::mutex> lock(lock_main);
		cv_main.wait(lock, [&]() {
			return mainStatus == 2;
		});
	}
}

// ����tagֵ
void LogSystem::SetTag(std::string tag, int value) {
	TagMapping[tag] = value;
}