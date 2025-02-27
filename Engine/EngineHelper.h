#ifndef _EngineHelper_H_
#define _EngineHelper_H_

#include <Windows.h>
#include "EngineConfig.h"

// 辅助函数
// 多字节转为宽字符 
bool CharToWChar(const char* szStr, WCHAR* wszClassName);

// 宽字节转多字节
char* WcharToChar(const wchar_t* wchar);

// ASCII 转 UTF_8
bool Ascii2Utf8(const char* szStr, WCHAR* wszClassName);

// 总和 
int Sum_Int(std::vector<int> check);

// 总和 
int Sum_Int(int* check, int len);

// 切割字符串 - 返回整形数值 
std::vector<int> Split_Int(const string strs, const string sub);

// 切割字符串 - 返回字符数值 
std::vector<string> Split(const string strs, const string sub);


#endif // !_EngineHelper_H_
