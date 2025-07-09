#ifndef _SImage_h_
#define _SImage_h_

#include "BaseSprite.h"


class SImage : public Sprite {
private:
	// ͼ��
	ID2D1Bitmap* _image;	// ͼ�����
	float opacity;			// ��͸����
	float angle;			// ��ת�Ƕ�
	D2D1_RECT_F src_rect;	// ��Դ�ü���

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

	// ����ͼ�� - �ⲿ�ṩͼ����Դ
	virtual void Draw(ID2D1Bitmap* _image);

	// ���û�������
	virtual void SetRect(D2D1_RECT_F _rect);

	// ������ת
	virtual void SetRotate(float angle);

	// ���òü�����
	virtual void SetCrop(D2D1_RECT_F cropRect);

	// ��ȡͼ��
	virtual ID2D1Bitmap* GetImage();

	// ��ȡ��ת
	virtual float GetRotate();

	// ��ȡ�ü�����
	virtual D2D1_RECT_F GetCrop();

	// ��������
	virtual void SaveToFile(const char* filename );

};

#endif // !_SImage_h_