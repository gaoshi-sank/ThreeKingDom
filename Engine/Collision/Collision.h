#ifndef _Collision_h_
#define _Collision_h_


// 判断点在区域内
bool Pos_In_Rect(int x, int y, int rect_left, int rect_top, int rect_right, int rect_bottom);

// 判定区域交互
// red 主区域， blue 判定区域
bool Rect_In_Rect(int red_left, int red_top, int red_right, int red_bottom, int blue_left, int blue_top, int blue_right, int blue_bottom);

// 区域交互
// red 主区域， blue 判定区域
// 1 = 不相交
// 2 = 区域内
// 3 = 其他
// 0 = 未知
int CheckRect(int red_left, int red_top, int red_right, int red_bottom, int blue_left, int blue_top, int blue_right, int blue_bottom);



#endif // !_Collision_h_
