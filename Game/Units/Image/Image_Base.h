#ifndef _Image_Base_h_
#define _Image_Base_h_

#include "../../Datas/DataProvider.h"
#include "../../../Engine/Render/Sprite/Animation.h"
#include "../../../Engine/Render/Sprite/SImage.h"

class Image_Base {
public:
	unsigned int image_id;

	// ����
	Image_Base();

	// ����
	~Image_Base();

	// ��ʼ��
	virtual void Create(int key) = 0;

	// ����
	virtual void Update() = 0;

	// ����
	virtual void Draw() = 0;
};


#endif // !_Image_Base_h_
