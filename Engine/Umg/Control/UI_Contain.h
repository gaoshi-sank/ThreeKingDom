#ifndef _UI_Contain_h_
#define _UI_Contain_h_


#include "../UI_Base.h"


class UI_Contain : public UI_Base {
public:
	int group;			// 组类
	int contain_type;	// 单选或多选

public:
	// 构造
	UI_Contain();
	
	// 析构
	~UI_Contain();

};


#endif // !_UI_Contain_h_
