#ifndef _BaseSprite_h_
#define _BaseSprite_h_

#include "../Render.h"	// ��Ⱦ��

// ����
const int limit_length = 1024;

// ������
class Sprite {
public:
	bool visiable;				// �ɼ���					
	D2D1_RECT_F draw_rect;		// ������

public:
	// ����
	Sprite() {
		visiable = true;
		draw_rect = D2D1::RectF();
	}

	// ����
	virtual ~Sprite() {

	}

	// ����
	virtual void Update() = 0;

	// ����
	virtual void Draw() = 0;

	// ���û�������
	virtual void SetRect(D2D1_RECT_F _rect) = 0;

	// ������ת
	virtual void SetRotate(float angle) = 0;
	
	// ��ȡͼ��
	virtual ID2D1Bitmap* GetImage() = 0;

	// ��ȡ����
	virtual D2D1_RECT_F GetRect() { return this->draw_rect; }

};

#endif // !_BaseSprite_h_
