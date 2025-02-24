#ifndef _UI_Base_h_
#define _UI_Base_h_

// 包含文件
#include "../Render/Sprite/SSprite.h"	// 渲染用精灵
#include "UIHelper.h"

// 控件
class UI_Base {
public:
	// 基础属性
	unsigned int window_id;		// 窗口编号 
	unsigned int window_style;	// 窗口类型 
	bool window_visible;		// 可见性
	bool window_release;		// 释放性
	bool window_top;			// 最顶层
	bool window_attached;		// 附属性
	bool window_key;			// 可触发键盘事件 
	bool window_mouse;			// 可触发鼠标事件
	int window_renderlevel;		// 窗口渲染层
	int window_x;				// 窗口区域 X
	int window_y;				// 窗口区域 Y
	int window_width;			// 窗口区域 width
	int window_height;			// 窗口区域 height

	// 事件属性
	int mouse_posx;				// 光标X
	int mouse_posy;				// 光标Y
	bool window_inrect;			// 区域内

public:
	// 枚举值
	// UI类型
	enum UIStyle {
		UIStyle_Base = 0,
		UIStyle_Lable,
		UIStyle_Button,
		UIStyle_Contain,
		UIStyle_CheckBox,
		UIStyle_Plane,
		UIStyle_Excel,
	};

	// UI消息
	enum UIMsgType {
		UIMsgType_None = 0,
		UIMsgType_Hover,		// 悬停
		UIMsgType_Down,			// 按下
		UIMsgType_Up,			// 放开
		UIMsgType_Click,		// 点击
	};

public:
	// 构造
	UI_Base();

	// 析构
	virtual ~UI_Base();

	// 预释放
	virtual void PreRelease() = 0;

	// 创建
	virtual bool Create() = 0;

	// 事件驱动
	virtual void CheckEvent(unsigned int* param) = 0;

	// 更新
	virtual void Update() = 0;

	// 绘制
	virtual void Draw() = 0;

	// 设置位置
	virtual void SetLocation(int x, int y) = 0;

	// 设置大小
	virtual void SetSize(int w, int h) = 0;

	// 设置可见性
	virtual void SetVisiable(bool visible = false) = 0;
};


#endif //!_UI_Base_h_