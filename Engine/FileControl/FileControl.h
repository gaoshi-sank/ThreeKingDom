#ifndef _FileControl_H_
#define _FileControl_H_

// 包含库
#include "../EngineConfig.h"			// 基础配置文件

#define DEBUG64 1


// 键值对 
class StringMap {
public:
	std::string key;		// 
	std::string value;	// 值

public:
	// 构造
	StringMap();

	// 构造
	// 参数 
	StringMap(string _key, string _value);

	// 复制构造
	StringMap(const StringMap& _other);

	// 析构 
	~StringMap();

	// 重载运算符
	StringMap& operator=(const StringMap& _other);

	// 判断是否空值
	bool Empty() const;

};

// 文件操作类
class FileControl {
public:
	// 构造
	FileControl();

	// 析构
	~FileControl();

	// 释放
	static void Release();

	// 初始化
	static void InitFileControl();

	// 转化路径
	static std::string ResPath(const char* filename);

	// 转化路径
	static std::string ResPath(std::string filename);

public:
	// 读取一行数据 
	// -1 结尾
	// 1 回车
	// 0 函数结束
	static int ReadLineString(std::string& result, FILE* fp = nullptr);

	// 读取键值对类型文件
	// 2 - 一个数据结束
	// -1 - 结尾
	// 0 - 函数结束
	static int ReadJson(std::vector<StringMap>& result, FILE* fp = nullptr);

};




#endif // !_FileControl_H_