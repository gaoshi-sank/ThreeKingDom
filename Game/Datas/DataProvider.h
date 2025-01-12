#ifndef _DataProvider_h_
#define _DataProvider_h_

#include "../../Engine/EngineConfig.h"

// ��Դ��ʽ
struct ResStruct {
	std::string path;	// ·��
	int width;			// ��ֿ��
	int height;			// ��ָ߶�

	ResStruct();
	ResStruct(const ResStruct& other);
	~ResStruct();
	ResStruct& operator=(const ResStruct& other);
};

// 
class DataProvider {
private:
	// ����
	DataProvider();

	// ����
	~DataProvider();
	
	// ��ֵ̬
	static DataProvider* g_data;

	// ����
	std::map<int, std::vector<ResStruct>> unitPath_List;
	std::map<int, std::vector<ResStruct>> buildPath_List;

public:
	// ��ȡ���
	static DataProvider* GetInstance();

	// �ͷ�
	static void Release();

	// ��ʼ��
	void InitData();

	// ��ȡ��λ��Դ·��
	std::vector<ResStruct> GetUnitPath(int key);

	// ��ȡ������Դ·��
	std::vector<ResStruct> GetBuildPath(int key);

private:
	// ��ʼ����λ��Դ·��
	void InitUnitResourcePath();

	// ��ʼ��������Դ·��
	void InitBuildResourcePath();

};


#endif // !_DataProvider_h_
