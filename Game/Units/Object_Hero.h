#ifndef _Object_Hero_h_
#define _Object_Hero_h_

#include "Object_Base.h"


class Object_Hero : public Object_Base {
private:
	std::shared_ptr<SImage> _test;
	bool InRect;
	int inhand_state;

public:
	// 构造
	Object_Hero();

	// 析构
	~Object_Hero();

	// 创建
	void Create(int key);

	// 创建部队
	void CreateHero(int x, int y);

	// 检查事件
	void CheckPoint(int x, int y);

	void CheckDown();
	void CheckUp();

	// 更新
	void Update();

	// 绘制
	void Draw();
};


#endif // !_Object_Hero_h_
