#include "DataProvider.h"
#include "../../Engine/FileControl/FileControl.h"
#include "../../Engine/Log/LogSystem.h"

// 静态值
DataProvider* DataProvider::g_data = nullptr;

ResStruct::ResStruct() {
	path = "";
	width = height = 0;
}

ResStruct::ResStruct(const ResStruct& other) : ResStruct(){
	if (this != &other) {
		this->path = other.path;
		this->width = other.width;
		this->height = other.height;
	}
}

ResStruct::~ResStruct() {

}


ResStruct& ResStruct::operator=(const ResStruct& other) {
	if (this != &other) {
		this->path = other.path;
		this->width = other.width;
		this->height = other.height;
	}
	return *this;
}

// 构造
DataProvider::DataProvider() {

}

// 析构
DataProvider::~DataProvider() {

}


// 获取句柄
DataProvider* DataProvider::GetInstance() {
	if (!g_data) {
		g_data = new DataProvider();
	}
	return g_data;
}

// 释放
void DataProvider::Release() {
	if (g_data) {
		delete g_data;
		g_data = nullptr;
	}
}

// 初始化
void DataProvider::InitData() {
	LogI("DataProvider::InitData +");

	// 初始化单位资源路径
	InitUnitResourcePath();

	// 初始化建筑资源路径
	InitBuildResourcePath();

	LogI("DataProvider::InitData -");
}

// 获取单位资源路径
std::vector<ResStruct> DataProvider::GetUnitPath(int key) {
	if (unitPath_List.count(key) == 1) {
		return unitPath_List[key];
	}
	return {};
}

// 获取建筑资源路径
std::vector<ResStruct> DataProvider::GetBuildPath(int key) {
	if (buildPath_List.count(key) == 1) {
		return buildPath_List[key];
	}
	return {};
}

// 初始化单位资源路径
void DataProvider::InitUnitResourcePath() {
	int key = 0x01;
	for (auto i = 0x01; i <= 0x01;i++) {
		// 获取并设置路径
		std::vector<ResStruct> lists;
		for (auto j = 0x01; j <= 0x08;j++) {
			std::string path = "Unit\\" + std::to_string(j) + "-1.png";
			std::string respath = FileControl::ResPath(path);

			// 新节点
			ResStruct newdata;
			newdata.path = respath;
			newdata.width = 36;
			newdata.height = 36;
			lists.push_back(newdata);
		}

		// 映射
		unitPath_List[key] = lists;
	}
}

// 初始化建筑资源路径
void DataProvider::InitBuildResourcePath() {
	int key = 0x01;
	for (auto i = 0x01; i <= 0x01; i++) {
		// 获取并设置路径
		std::vector<ResStruct> lists;
		for (auto j = 0x01; j <= 0x0b; j++) {
			std::string path = "Build\\" + std::to_string(j) + "-1.png";
			std::string respath = FileControl::ResPath(path);

			// 新节点
			ResStruct newdata;
			newdata.path = respath;
			newdata.width = 1;
			newdata.height = 1;
			lists.push_back(newdata);
		}

		// 映射
		buildPath_List[key] = lists;
	}
}