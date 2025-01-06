#include "UI_Base.h"
#include "UIFactory.h"

static unsigned int baseid = 0x00;

// 构造
UI_Base::UI_Base() {
	// 基础属性
	this->window_id = ++baseid;				// 窗口编号 
	this->window_style = UIStyle_Base;		// 窗口类型 
	this->window_visible = true;			// 默认 - 可见
	this->window_release = false;			// 默认 - 未释放
	this->window_top = false;				// 默认 - 最低层
	this->window_attached = false;			// 默认 - 单独控件
	this->window_key = false;				// 默认 - 不触发键盘 
	this->window_mouse = true;				// 默认 - 可触发鼠标 
	this->window_renderlevel = 0x00;		// 默认 - 渲染层 0

	// 事件属性
	mouse_posx = mouse_posy = 0;
	window_inrect = false;
	
	// 窗口属性
	this->window_x = this->window_y = this->window_width = this->window_height = 0;

	// 加入管理
	UIFactory::AddWindow(this);
}

// 析构
UI_Base::~UI_Base() {

}

// 基础事件
void UI_Base::CheckEvent(unsigned int* param) {
	if (window_release || !param) {
		return;
	}

	int param_len = param[0];
	if (param_len >= 2) {
		auto message = param[1];

		// 基础光标位置
		if (window_mouse && message == WM_MOUSEMOVE) {
			// 默认不在窗口
			window_inrect = false;	

			// 正确获取
			if (param_len >= 3) {
				LPARAM lParam = (LPARAM)param[2];
				mouse_posx = GET_X_LPARAM(lParam);
				mouse_posy = GET_Y_LPARAM(lParam);

				// 判断顶层
				window_top = UIFactory::GetLevelTop(mouse_posx, mouse_posy, this);

				// 判断区域内
				if (window_top && Point_In_Rect(mouse_posx, mouse_posy, window_x, window_y, window_width, window_height)) {
					window_inrect = true;
				}
			}
		}
	}
}