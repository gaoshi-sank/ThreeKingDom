#ifndef _Object_Amry_h_
#define _Object_Amry_h_

#include "Image/Image_Army.h"
#include "Object_Base.h"

class Object_Army : public Object_Base {
private:
	std::shared_ptr<Image_Army> image;



public:
	// ����
	Object_Army();

	// ����
	~Object_Army();

	// ����
	void Create(int key);

	// ��������
	void CreateAmry(int x, int y);

	// ����������
	void SetFace(int face);

	// ����
	void Update();

	// ����
	void Draw();
};


#endif // !_Object_Amry_h_
