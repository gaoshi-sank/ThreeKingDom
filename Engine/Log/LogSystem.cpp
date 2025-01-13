#include "LogSystem.h"
#include "../FileControl/FileControl.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

// ��ֵ̬
static LogSystem* g_log = nullptr;
static std::string debugConfig = "debugConfig.txt";		// debug����
static std::string logFile = "logFile.txt";				// log����ļ�

// logϵͳ���ڴ��
static std::shared_ptr<MemPool> logPool = std::make_shared<MemPool>(32, 128);	


// ��ȡʱ���
static std::string getCurrentTimestampString() {
	// ��ȡ��ǰʱ���
	auto now = std::chrono::system_clock::now();

	// ��ʱ���ת��Ϊtime_t���ͣ�����C�������ʱ�亯����ʹ�õ�����
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

	// ��time_t����ת��Ϊtm�ṹ�壬�������ǾͿ��Է����ꡢ�¡��յ���Ϣ
	std::tm* now_tm = std::localtime(&now_time_t);

	// ����һ���ַ�������������ʽ���ַ���
	std::ostringstream oss;

	// ʹ��strftime����ʽ�����ں�ʱ�䣬��ע��strftime����ֱ���ṩ����
	oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");

	// ��ȡ���벿��
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		now.time_since_epoch() % std::chrono::seconds(1)
	).count();

	// �������ʽ��Ϊ��λ���ֲ���ӵ��ַ�����
	oss << '.' << std::setfill('0') << std::setw(3) << ms;

	// ���ظ�ʽ������ַ���
	return oss.str();
}

// д��log
void LogI(std::string tag, const char* format, ...) {
	if (logPool) {
		va_list args;
		va_start(args, format);

		auto bufferlen = vsnprintf(nullptr, 0, format, args) + 1;
		if (bufferlen > 0) {
			// ����buffer
			char* buffer = logPool->GetBuffer<char>(bufferlen);
			memset(buffer, '\0', sizeof(char) * bufferlen);
			vsnprintf(buffer, bufferlen, format, args);

			// ��ȡʱ���
			auto timestamp = getCurrentTimestampString();

			// ƴ��
			auto newlen = snprintf(nullptr, 0, "%s %s %s", timestamp.c_str(), tag.c_str(), buffer);
			if (newlen > 0) {
				char* newBuffer = logPool->GetBuffer<char>(newlen);
				memset(newBuffer, '\0', sizeof(char) * newlen);

				// ����logϵͳ
				if (g_log) {
					snprintf(newBuffer, newlen, "%s %s %s", timestamp.c_str(), tag.c_str(), buffer);
					g_log->Enque(newBuffer, newlen);
				}

				// �ͷ�������ڴ�
				logPool->ReleaseBuffer(newBuffer);
			}

			// �ͷ�������ڴ�
			logPool->ReleaseBuffer(buffer);
		}
		va_end(args);
	}
}

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

// enque
void LogSystem::Enque(char* buffer, int len) {
	if (len > 0) {
		char* _data = logPool->GetBuffer<char>(len);
		if (_data) {
			memset(_data, '\0', sizeof(char) * len);
			memcpy(_data, buffer, sizeof(char) * len);

			{
				std::unique_lock<std::mutex> lock(lock_buffer);
				this->bufferList.push(_data);
			}
		}
	}
}

// �����̴߳���
void LogSystem::ThreadLoop() {
	// �����ļ�
	FILE* fp = fopen(logFile.c_str(), "w");

	// ѭ������log��Ϣ
	while (mainStatus && fp) {
		// ����logд��
		if(!bufferList.empty()){
			std::unique_lock<std::mutex> lock(lock_buffer);
			do{
				auto buffer = bufferList.front();	// ��ȡ
				if (buffer) {
					fprintf(fp, "%s", buffer);		// д���ļ�
					logPool->ReleaseBuffer(buffer);	// �ͷ��ڴ�
					bufferList.pop();				// �����б�
				}
			} while (!bufferList.empty());
		}
	}

	// �ر��ļ�
	if (fp) {
		fclose(fp);
		fp = nullptr;
	}

	// ����״̬֪ͨ�߳̽���
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