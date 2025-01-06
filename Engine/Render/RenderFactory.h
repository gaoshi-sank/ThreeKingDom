#ifndef _RenderFactory_h_
#define _RenderFactory_h_


#include "Render.h"


// 渲染工厂
class RenderFactory {
public:
	// 渲染器类型
	enum RenderType {
		RenderType_Direct2D = 1,	// Direct2D
	};

private:
	// 构造
	RenderFactory();

	// 析构
	~RenderFactory();

	// 属性
	int renderType;
	Render* g_render;

	// Direct2D用参数
	HWND g_hWnd;
	int direct2d_width, direct2d_height;

	// 静态值
	static RenderFactory* g_renderFactory;

public:
	// 初始化渲染器
	// RenderType_Direct2D: 窗口句柄，窗口宽度，窗口高度
	static void InitRender(int renderType, ...);

	// 获取渲染器工厂
	static RenderFactory* GetInstance();

	// 释放
	static void Release();

	// 获取渲染器
	Render* GetRender();

private:
	// 初始化Diect2D类型渲染器
	void InitRender_Direct2D();

};



#endif // !_RenderFactory_h_