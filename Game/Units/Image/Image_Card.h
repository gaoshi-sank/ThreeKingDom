/*
* ������ - ͼ����Ⱦ����
*/
#ifndef _Image_Card_h_
#define _Image_Card_h_

#include "Image_Base.h"

class Image_Card : public Image_Base {
public:
	// ����
	Image_Card();

	// ����
	~Image_Card();

	// ��ʼ��
	virtual void Create(int key);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();
};


#endif // !_Image_Card_h_
