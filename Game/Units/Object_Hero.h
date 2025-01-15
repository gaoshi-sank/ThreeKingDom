#ifndef _Object_Hero_h_
#define _Object_Hero_h_

#include "Object_Base.h"


class Object_Hero : public Object_Base {
private:
	std::shared_ptr<SImage> _test;

public:
	// ����
	Object_Hero();

	// ����
	~Object_Hero();

	// ����
	void Create(int key);

	// ��������
	void CreateHero(int x, int y);

	// ����
	void Update();

	// ����
	void Draw();
};


#endif // !_Object_Hero_h_
