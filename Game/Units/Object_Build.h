#ifndef _Object_Build_h_
#define _Object_Build_h_

#include "Image/Image_Build.h"
#include "Object_Base.h"

class Object_Build : public Object_Base {
private:
	std::shared_ptr<Image_Build> image;



public:
	// ����
	Object_Build();

	// ����
	~Object_Build();

	// ����
	void Create(int key);

	// ��������
	void CreateBuild(int x, int y);

	// ����
	void Update();

	// ����
	void Draw();


};


#endif // !_Object_Build_h_
