#ifndef _Data_Army_h_
#define _Data_Army_h_

#include "Data_Base.h"


// �ṹ�� -- ����
// ����
class Data_Army : public Data_Base {
public:
	unsigned int army_id;			// ���ӱ��
	unsigned int player_id;			// ��ұ��
	unsigned int solder_number;		// ʿ������
	unsigned int solder_feeling;	// ʿ��ʿ��
	unsigned int general_id;		// ��
	unsigned int hero_lists[4];		// �佫�б�

};



#endif // !_Data_Army_h_

