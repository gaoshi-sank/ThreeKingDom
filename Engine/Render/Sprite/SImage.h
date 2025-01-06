#ifndef _SImage_h_
#define _SImage_h_

#include "BaseSprite.h"


class SImage : public Sprite {
private:
	// ͼ��
	void* _image;				// ͼ�����
	float opacity;				// ��͸����
	float angle;				// ��ת�Ƕ�
	int src_x, src_y,
		src_width, src_height;	// ��Դ�ü���

public:
	// ����
	SImage();

	// ����
	SImage(const char* filename);

	// ����
	~SImage();

	// ����
	virtual void Update();

	// ����ͼ��
	virtual void Draw();

	// ���û���λ��
	virtual void SetLocaiton(int x, int y);

	// ���û��ƴ�С
	virtual void SetSize(int w, int h);

	// ������ת 
	virtual void SetRotate(float angle);

	// ���òü�
	virtual void SetCrop(int x, int y, int width, int height);

	// ��ȡͼ���С
	virtual bool GetImageSize(int& width, int& height);
};

#endif // !_SImage_h_