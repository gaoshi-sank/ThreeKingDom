#include "DataProvider.h"
#include "../../Engine/FileControl/FileControl.h"
#include "../../Engine/Log/LogSystem.h"

// ��ֵ̬
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

// ����
DataProvider::DataProvider() {

}

// ����
DataProvider::~DataProvider() {

}


// ��ȡ���
DataProvider* DataProvider::GetInstance() {
	if (!g_data) {
		g_data = new DataProvider();
	}
	return g_data;
}

// �ͷ�
void DataProvider::Release() {
	if (g_data) {
		delete g_data;
		g_data = nullptr;
	}
}

// ��ʼ��
void DataProvider::InitData() {
	LogI("DataProvider::InitData +");

	// ��ʼ����λ��Դ·��
	InitUnitResourcePath();

	// ��ʼ��������Դ·��
	InitBuildResourcePath();

	LogI("DataProvider::InitData -");
}

// ��ȡ��λ��Դ·��
std::vector<ResStruct> DataProvider::GetUnitPath(int key) {
	if (unitPath_List.count(key) == 1) {
		return unitPath_List[key];
	}
	return {};
}

// ��ȡ������Դ·��
std::vector<ResStruct> DataProvider::GetBuildPath(int key) {
	if (buildPath_List.count(key) == 1) {
		return buildPath_List[key];
	}
	return {};
}

// ��ʼ����λ��Դ·��
void DataProvider::InitUnitResourcePath() {
	int key = 0x01;
	for (auto i = 0x01; i <= 0x01;i++) {
		// ��ȡ������·��
		std::vector<ResStruct> lists;
		for (auto j = 0x01; j <= 0x08;j++) {
			std::string path = "Unit\\" + std::to_string(j) + "-1.png";
			std::string respath = FileControl::ResPath(path);

			// �½ڵ�
			ResStruct newdata;
			newdata.path = respath;
			newdata.width = 36;
			newdata.height = 36;
			lists.push_back(newdata);
		}

		// ӳ��
		unitPath_List[key] = lists;
	}
}

// ��ʼ��������Դ·��
void DataProvider::InitBuildResourcePath() {
	int key = 0x01;
	for (auto i = 0x01; i <= 0x01; i++) {
		// ��ȡ������·��
		std::vector<ResStruct> lists;
		for (auto j = 0x01; j <= 0x0b; j++) {
			std::string path = "Build\\" + std::to_string(j) + "-1.png";
			std::string respath = FileControl::ResPath(path);

			// �½ڵ�
			ResStruct newdata;
			newdata.path = respath;
			newdata.width = 1;
			newdata.height = 1;
			lists.push_back(newdata);
		}

		// ӳ��
		buildPath_List[key] = lists;
	}
}