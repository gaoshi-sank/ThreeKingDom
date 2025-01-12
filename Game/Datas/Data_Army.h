#ifndef _Data_Army_h_
#define _Data_Army_h_

#include "Data_Base.h"


// 结构体 -- 部队
// 数据
class Data_Army : public Data_Base {
public:
	unsigned int army_id;			// 部队编号
	unsigned int player_id;			// 玩家编号
	unsigned int solder_number;		// 士兵数量
	unsigned int solder_feeling;	// 士兵士气
	unsigned int general_id;		// 大将
	unsigned int hero_lists[4];		// 武将列表

};



#endif // !_Data_Army_h_

