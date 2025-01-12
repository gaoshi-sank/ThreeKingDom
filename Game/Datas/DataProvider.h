#ifndef _DataProvider_h_
#define _DataProvider_h_

#include "../../Engine/EngineConfig.h"

// 资源格式
struct ResStruct {
	std::string path;	// 路径
	int width;			// 拆分宽度
	int height;			// 拆分高度

	ResStruct();
	ResStruct(const ResStruct& other);
	~ResStruct();
	ResStruct& operator=(const ResStruct& other);
};

// 
class DataProvider {
private:
	// 构造
	DataProvider();

	// 析构
	~DataProvider();
	
	// 静态值
	static DataProvider* g_data;

	// 属性
	std::map<int, std::vector<ResStruct>> unitPath_List;
	std::map<int, std::vector<ResStruct>> buildPath_List;

public:
	// 获取句柄
	static DataProvider* GetInstance();

	// 释放
	static void Release();

	// 初始化
	void InitData();

	// 获取单位资源路径
	std::vector<ResStruct> GetUnitPath(int key);

	// 获取建筑资源路径
	std::vector<ResStruct> GetBuildPath(int key);

private:
	// 初始化单位资源路径
	void InitUnitResourcePath();

	// 初始化建筑资源路径
	void InitBuildResourcePath();

};


#endif // !_DataProvider_h_
