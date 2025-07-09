#ifndef _Collision_h_
#define _Collision_h_

#include <d2d1.h>				// 2d

// �жϵ���������
bool Pos_In_Rect(float x, float y, float rect_left, float rect_top, float rect_right, float rect_bottom);

// �ж����򽻻�
// red ������ blue �ж�����
bool Rect_In_Rect(float red_left, float red_top, float red_right, float red_bottom, float blue_left, float blue_top, float blue_right, float blue_bottom);

// ���򽻻�
// red ������ blue �ж�����
// 1 = ���ཻ
// 2 = ������
// 3 = ����
// 0 = δ֪
int CheckRect(float red_left, float red_top, float red_right, float red_bottom, float blue_left, float blue_top, float blue_right, float blue_bottom);

// ���򽻻�
// red ������ blue �ж�����
// 1 = ���ཻ
// 2 = ������
// 3 = ����
// 0 = δ֪
int CheckRect(D2D1_RECT_F rect1, D2D1_RECT_F rect2);

//  ���ĵ�
enum CenterType {
	CenterType_None = 0,
	CenterType_LT,
	CenterType_RT,
	CenterType_LB,
	CenterType_RB,
	CenterType_CN,
};

// ��ײ����
class Collision {
public:
	float box_x;			// X��
	float box_y;			// Y��
	float box_width;		// ���
	float box_height;		// �߶�
	int default_center;		// Ĭ�����ĵ�
	float G, V;				// �������ٶȣ�ˮƽ���ٶ�
	float speed_x, speed_y;	// ˮƽ�ٶȣ���ֱ�ٶ�

	Collision();

	virtual ~Collision();
};

#endif // !_Collision_h_
