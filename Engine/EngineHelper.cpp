#include "EngineHelper.h"


// ��������
// ���ֽ�תΪ���ַ� 
bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// ת�� 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}

	return result;
}

// ���ֽ�ת���ֽ�
char* WcharToChar(const wchar_t* wchar){
	char* pchar = nullptr;
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, (int)wcslen(wchar), NULL, 0, NULL, NULL);
	if (len > 0) {
		pchar = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wchar, (int)wcslen(wchar), pchar, len, NULL, NULL);
		pchar[len] = '\0';
	}
	return pchar;
}

// ASCII ת UTF_8
bool Ascii2Utf8(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// ת�� 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_UTF8, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}
	return result;
}

// �ܺ� 
int Sum_Int(std::vector<int> check) {
	int result;
	std::vector<int>::iterator it;

	// 
	result = 0;
	for (it = check.begin(); it != check.end(); it++) {
		result += (*it);
	}

	return result;
}

// �ܺ� 
int Sum_Int(int* check, int len) {
	int result = 0;
	int i = 0;

	// ����Ӻ� 
	if (check != nullptr && len > 0) {
		for (i = 0; i < len; i++) {
			result += check[i];
		}
	}

	return result;
}


// �и��ַ��� - �����ַ���ֵ 
std::vector<string> Split(const string strs, const string sub) {
	// ��� 
	std::vector<string> result;
	size_t start = 0, index = 0;

	//
	if (sub.empty()) {
		return result;
	}

	// ѭ������ 
	index = strs.find_first_of(sub, 0);
	while (index != strs.npos) {
		// λ�ú�������һ�� 
		if (start != index) {
			result.push_back(strs.substr(start, index - start));
		}

		// ������һ��λ�� 
		start = index + 1;
		index = strs.find_first_of(sub, start);
	}

	if (!strs.substr(start).empty()) {
		result.push_back(strs.substr(start));
	}

	return result;
}
