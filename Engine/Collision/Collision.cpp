#include "Collision.h"

// 判断点在区域内
bool Pos_In_Rect(float x, float y, float rect_left, float rect_top, float rect_right, float rect_bottom) {
	if (rect_left <= x && x <= rect_right) {
		if (rect_top <= y && y <= rect_bottom) {
			return true;
		}
	}
	return false;
}

// 判定区域交互
// red 主区域， blue 判定区域
bool Rect_In_Rect(float red_left, float red_top, float red_right, float red_bottom, float blue_left, float blue_top, float blue_right, float blue_bottom) {
	// 完全处于 [ [] ]
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

// 区域交互
// red 主区域， blue 判定区域
// 1 = 不相交
// 2 = 区域内
// 3 = 其他
// 0 = 未知
int CheckRect(float red_left, float red_top, float red_right, float red_bottom, float blue_left, float blue_top, float blue_right, float blue_bottom) {
	// 不交集
	if ((blue_left < red_left && blue_right < red_left) ||			// 判定在主区域左边
		(blue_left > red_right && blue_right > red_left) ||			// 判定在主区域右边
		(blue_top < red_top && blue_bottom < red_top) ||			// 判定在主区域上边
		(blue_top > red_bottom && blue_bottom > red_bottom) 		// 判定在主区域下边
		) {
		return 1;
	}
	else {
		// 区域内
		if (Rect_In_Rect(red_left, red_top, red_right, red_bottom, blue_left, blue_top, blue_right, blue_bottom)) {
			return 2;
		}
		// 其他
		else {
			return 3;
		}
	}
	return 0;
}

// 区域交互
// red 主区域， blue 判定区域
// 1 = 不相交
// 2 = 区域内
// 3 = 其他
// 0 = 未知
int CheckRect(D2D1_RECT_F rect1, D2D1_RECT_F rect2) {
	return CheckRect(rect1.left, rect1.top, rect1.right, rect1.bottom, rect2.left, rect2.top, rect2.right, rect2.bottom);
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