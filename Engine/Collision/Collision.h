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



#endif // !_Collision_h_
