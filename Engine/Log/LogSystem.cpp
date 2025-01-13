#include "LogSystem.h"
#include "../FileControl/FileControl.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

// 静态值
static LogSystem* g_log = nullptr;
static std::string debugConfig = "debugConfig.txt";		// debug配置
static std::string logFile = "logFile.txt";				// log输出文件

// log系统的内存池
static std::shared_ptr<MemPool> logPool = std::make_shared<MemPool>(32, 128);	


// 获取时间戳
static std::string getCurrentTimestampString() {
	// 获取当前时间点
	auto now = std::chrono::system_clock::now();

	// 将时间点转换为time_t类型，这是C风格日期时间函数所使用的类型
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

	// 将time_t类型转换为tm结构体，这样我们就可以访问年、月、日等信息
	std::tm* now_tm = std::localtime(&now_time_t);

	// 创建一个字符串流来构建格式化字符串
	std::ostringstream oss;

	// 使用strftime来格式化日期和时间，但注意strftime不会直接提供毫秒
	oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");

	// 获取毫秒部分
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		now.time_since_epoch() % std::chrono::seconds(1)
	).count();

	// 将毫秒格式化为三位数字并添加到字符串中
	oss << '.' << std::setfill('0') << std::setw(3) << ms;

	// 返回格式化后的字符串
	return oss.str();
}

// 写入log
void LogI(std::string tag, const char* format, ...) {
	if (logPool) {
		va_list args;
		va_start(args, format);

		auto bufferlen = vsnprintf(nullptr, 0, format, args) + 1;
		if (bufferlen > 0) {
			// 申请buffer
			char* buffer = logPool->GetBuffer<char>(bufferlen);
			memset(buffer, '\0', sizeof(char) * bufferlen);
			vsnprintf(buffer, bufferlen, format, args);

			// 获取时间戳
			auto timestamp = getCurrentTimestampString();

			// 拼接
			auto newlen = snprintf(nullptr, 0, "%s %s %s", timestamp.c_str(), tag.c_str(), buffer);
			if (newlen > 0) {
				char* newBuffer = logPool->GetBuffer<char>(newlen);
				memset(newBuffer, '\0', sizeof(char) * newlen);

				// 加入log系统
				if (g_log) {
					snprintf(newBuffer, newlen, "%s %s %s", timestamp.c_str(), tag.c_str(), buffer);
					g_log->Enque(newBuffer, newlen);
				}

				// 释放申请的内存
				logPool->ReleaseBuffer(newBuffer);
			}

			// 释放申请的内存
			logPool->ReleaseBuffer(buffer);
		}
		va_end(args);
	}
}

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

// 独立线程处理
void LogSystem::ThreadLoop() {
	// 生成文件
	FILE* fp = fopen(logFile.c_str(), "w");

	// 循环处理log消息
	while (mainStatus && fp) {
		// 处理log写入
		if(!bufferList.empty()){
			std::unique_lock<std::mutex> lock(lock_buffer);
			do{
				auto buffer = bufferList.front();	// 获取
				if (buffer) {
					fprintf(fp, "%s", buffer);		// 写入文件
					logPool->ReleaseBuffer(buffer);	// 释放内存
					bufferList.pop();				// 弹出列表
				}
			} while (!bufferList.empty());
		}
	}

	// 关闭文件
	if (fp) {
		fclose(fp);
		fp = nullptr;
	}

	// 设置状态通知线程结束
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