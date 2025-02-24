#include "Collision.h"

// �жϵ���������
bool Pos_In_Rect(int x, int y, int rect_left, int rect_top, int rect_right, int rect_bottom) {
	if (rect_left <= x && x <= rect_right) {
		if (rect_top <= y && y <= rect_bottom) {
			return true;
		}
	}
	return false;
}

// �ж����򽻻�
// red ������ blue �ж�����
bool Rect_In_Rect(int red_left, int red_top, int red_right, int red_bottom, int blue_left, int blue_top, int blue_right, int blue_bottom) {
	// ��ȫ���� [ [] ]
	if ((red_left < blue_left && blue_left < red_right) && (red_left < blue_right && blue_right < red_right)) {
		if ((red_top < blue_top && blue_top < red_bottom) && (red_top < blue_bottom && blue_bottom < red_bottom)) {
			if (red_left < red_right && red_top < red_bottom && 
				blue_left < blue_right && blue_top < blue_bottom) {
				return true;
			}
		}
	}

	return false;
}

// ���򽻻�
// red ������ blue �ж�����
// 1 = ���ཻ
// 2 = ������
// 3 = ����
// 0 = δ֪
int CheckRect(int red_left, int red_top, int red_right, int red_bottom, int blue_left, int blue_top, int blue_right, int blue_bottom) {
	// ������
	if ((blue_left < red_left && blue_right < red_left) ||			// �ж������������
		(blue_left > red_right && blue_right > red_left) ||			// �ж����������ұ�
		(blue_top < red_top && blue_bottom < red_top) ||			// �ж����������ϱ�
		(blue_top > red_bottom && blue_bottom > red_bottom) 		// �ж����������±�
		) {
		return 1;
	}
	else {
		// ������
		if (Rect_In_Rect(red_left, red_top, red_right, red_bottom, blue_left, blue_top, blue_right, blue_bottom)) {
			return 2;
		}
		// ����
		else {
			return 3;
		}
	}
	return 0;
}



Collision::Collision() {
	box_x = 0.0f;
	box_y = 0.0f;
	box_width = 0.0f;
	box_height = 0.0f;
	default_center = CenterType_LT;
	speed_x = speed_y = 0.0f;
	V = 0.0f;
	G = 0.0f;
}

Collision::~Collision() {

}