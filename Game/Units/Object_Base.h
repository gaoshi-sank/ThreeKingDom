#ifndef _Object_Base_h_
#define _Object_Base_h_

#include "Image/Image_Base.h"

class Object_Base {
public:
	unsigned int object_id;

	// ����
	Object_Base();

	// ����
	~Object_Base();

	// ��ʼ��
	virtual void Create(int key) = 0;

	// ����
	virtual void Update() = 0;

	// ����
	virtual void Draw() = 0;
};



#endif // !_Object_Base_h_
