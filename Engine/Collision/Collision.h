#ifndef _Collision_h_
#define _Collision_h_


// �жϵ���������
bool Pos_In_Rect(int x, int y, int rect_left, int rect_top, int rect_right, int rect_bottom);

// �ж����򽻻�
// red ������ blue �ж�����
bool Rect_In_Rect(int red_left, int red_top, int red_right, int red_bottom, int blue_left, int blue_top, int blue_right, int blue_bottom);

// ���򽻻�
// red ������ blue �ж�����
// 1 = ���ཻ
// 2 = ������
// 3 = ����
// 0 = δ֪
int CheckRect(int red_left, int red_top, int red_right, int red_bottom, int blue_left, int blue_top, int blue_right, int blue_bottom);

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
