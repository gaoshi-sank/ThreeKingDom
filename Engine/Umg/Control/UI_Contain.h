#ifndef _UI_Contain_h_
#define _UI_Contain_h_


#include "../UI_Base.h"


class UI_Contain : public UI_Base {
public:
	int group;			// ����
	int contain_type;	// ��ѡ���ѡ

public:
	// ����
	UI_Contain();
	
	// ����
	~UI_Contain();

};


#endif // !_UI_Contain_h_
