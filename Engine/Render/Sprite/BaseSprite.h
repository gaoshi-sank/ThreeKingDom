#ifndef _BaseSprite_h_
#define _BaseSprite_h_

#include "../Render.h"	// ��Ⱦ��

// ����
const int limit_length = 1024;

// ������
class Sprite {
public:
	bool visiable;					// �ɼ���					
	int draw_x, draw_y, 
		draw_width, draw_height;	// ������

public:
	// ����
	Sprite() {
		visiable = true;
		draw_x = draw_y = draw_width = draw_height = 0;
	}

	// ����
	virtual ~Sprite() {

	}

	// ����
	virtual void Update() = 0;

	// ����
	// ͼ��ͼ�Ρ��������ı�
	virtual void Draw() = 0;

	// ���û���λ��
	virtual void SetLocaiton(int x, int y) = 0;

	// ���û��ƴ�С
	virtual void SetSize(int w, int h) = 0;

	// ������ת
	virtual void SetRotate(float angle) = 0;

};

#endif // !_BaseSprite_h_
