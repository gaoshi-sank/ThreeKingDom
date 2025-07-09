#ifndef _Collision_h_
#define _Collision_h_

#include <d2d1.h>				// 2d

// 判断点在区域内
bool Pos_In_Rect(float x, float y, float rect_left, float rect_top, float rect_right, float rect_bottom);

// 判定区域交互
// red 主区域， blue 判定区域
bool Rect_In_Rect(float red_left, float red_top, float red_right, float red_bottom, float blue_left, float blue_top, float blue_right, float blue_bottom);

// 区域交互
// red 主区域， blue 判定区域
// 1 = 不相交
// 2 = 区域内
// 3 = 其他
// 0 = 未知
int CheckRect(float red_left, float red_top, float red_right, float red_bottom, float blue_left, float blue_top, float blue_right, float blue_bottom);

// 区域交互
// red 主区域， blue 判定区域
// 1 = 不相交
// 2 = 区域内
// 3 = 其他
// 0 = 未知
int CheckRect(D2D1_RECT_F rect1, D2D1_RECT_F rect2);

//  中心点
enum CenterType {
	CenterType_None = 0,
	CenterType_LT,
	CenterType_RT,
	CenterType_LB,
	CenterType_RB,
	CenterType_CN,
};

// 碰撞盒子
class Collision {
public:
	float box_x;			// X轴
	float box_y;			// Y轴
	float box_width;		// 宽度
	float box_height;		// 高度
	int default_center;		// 默认中心点
	float G, V;				// 重力加速度，水平加速度
	float speed_x, speed_y;	// 水平速度，垂直速度

	Collision();

	virtual ~Collision();
};

#endif // !_Collision_h_
