#include "CameraView.h"

// 构造
CameraView::CameraView() {
	rect_x = rect_y = rect_width = rect_height = 0;
	width = height = 0;
}

// 构造
// 参数 - 视口大小
CameraView::CameraView(int rect_x, int rect_y, int rect_width, int rect_height) :CameraView() {
	this->rect_x = rect_x;
	this->rect_y = rect_y;
	this->rect_width = rect_width;
	this->rect_height = rect_height;
	this->width = (float)rect_width;
	this->height = (float)rect_height;
}

// 析构
CameraView::~CameraView() {

}

// 更新
void CameraView::Update(int face, float step) {
	// 保留范围
	auto temp_x = rect_x;
	auto temp_y = rect_y;
	auto temp_width = rect_width;
	auto temp_height = rect_height;
	step = abs(step);

	// 位移
	if (face == 4) {
		temp_x -= (int)step;
		if (temp_x <= 0) {
			temp_x = 0;
		}
	}
	else if (face == 6) {
		temp_x += (int)step;
		if (temp_x >= 50 * 200) {	// 这个范围应该由地图提供
			temp_x = 50 * 200;
		}
	}
	else if (face == 8) {
		temp_y -= (int)step;
		if (temp_y <= 0) {
			temp_y = 0;
		}
	}
	else if (face == 2) {
		temp_y += (int)step;
		if (temp_y >= 50 * 200) {	// 这个范围应该由地图提供
			temp_y = 50 * 200;
		}
	}


	// 更新
	this->rect_x = temp_x;
	this->rect_y = temp_y;
	this->rect_width = temp_width;
	this->rect_height = temp_height;
}