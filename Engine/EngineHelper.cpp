#include "EngineHelper.h"


// 辅助函数
// 多字节转为宽字符 
bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// 转换 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}

	return result;
}

// 宽字节转多字节
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

// ASCII 转 UTF_8
bool Ascii2Utf8(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// 转换 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_UTF8, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}
	return result;
}

// 总和 
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

// 总和 
int Sum_Int(int* check, int len) {
	int result = 0;
	int i = 0;

	// 计算加合 
	if (check != nullptr && len > 0) {
		for (i = 0; i < len; i++) {
			result += check[i];
		}
	}

	return result;
}


// 切割字符串 - 返回字符数值 
std::vector<string> Split(const string strs, const string sub) {
	// 结果 
	std::vector<string> result;
	size_t start = 0, index = 0;

	//
	if (sub.empty()) {
		return result;
	}

	// 循环查找 
	index = strs.find_first_of(sub, 0);
	while (index != strs.npos) {
		// 位置和索引不一致 
		if (start != index) {
			result.push_back(strs.substr(start, index - start));
		}

		// 查找下一个位置 
		start = index + 1;
		index = strs.find_first_of(sub, start);
	}

	if (!strs.substr(start).empty()) {
		result.push_back(strs.substr(start));
	}

	return result;
}
