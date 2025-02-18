/*
* 视口对象
*	用于绘制画面
*/
#ifndef _CameraView_H_
#define _CameraView_H_

#include "../../Engine/Render/RenderFactory.h"

// 结构体 - 地图视口
class CameraView {
public:
	int rect_x, rect_y,
		rect_width, rect_height;	// 视野区域
	float width, height;			// 宽度，高度

public:
	// 构造
	CameraView();

	// 构造
	// 参数 - 视口大小
	CameraView(int rect_x, int rect_y, int rect_width, int rect_height);

	// 析构
	~CameraView();

	// 更新
	void Update(int face, float step);
};

#endif // !_CameraView_H_
