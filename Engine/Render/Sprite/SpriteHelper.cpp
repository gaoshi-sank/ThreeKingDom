#include "SpriteHelper.h"


// 多字节转为宽字符 
bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	bool result = false;
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

