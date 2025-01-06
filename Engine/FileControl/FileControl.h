#ifndef _FileControl_H_
#define _FileControl_H_

// ������
#include "../EngineConfig.h"			// ���������ļ�

#define DEBUG64 1


// ��ֵ�� 
class StringMap {
public:
	std::string key;		// 
	std::string value;	// ֵ

public:
	// ����
	StringMap();

	// ����
	// ���� 
	StringMap(string _key, string _value);

	// ���ƹ���
	StringMap(const StringMap& _other);

	// ���� 
	~StringMap();

	// ���������
	StringMap& operator=(const StringMap& _other);

	// �ж��Ƿ��ֵ
	bool Empty() const;

};

// �ļ�������
class FileControl {
public:
	// ����
	FileControl();

	// ����
	~FileControl();

	// �ͷ�
	static void Release();

	// ��ʼ��
	static void InitFileControl();

	// ת��·��
	static std::string ResPath(const char* filename);

	// ת��·��
	static std::string ResPath(std::string filename);

public:
	// ��ȡһ������ 
	// -1 ��β
	// 1 �س�
	// 0 ��������
	static int ReadLineString(std::string& result, FILE* fp = nullptr);

	// ��ȡ��ֵ�������ļ�
	// 2 - һ�����ݽ���
	// -1 - ��β
	// 0 - ��������
	static int ReadJson(std::vector<StringMap>& result, FILE* fp = nullptr);

};




#endif // !_FileControl_H_