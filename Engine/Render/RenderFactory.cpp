#include "RenderFactory.h"
#include "Direct2D/Render_Direct2d.h"
#include <stdarg.h>

RenderFactory* RenderFactory::g_renderFactory = nullptr;;


// 构造
RenderFactory::RenderFactory() {
	renderType = RenderType_Direct2D;
	g_render = nullptr;

	// Direct2d渲染器类型参数
	g_hWnd = nullptr;
	direct2d_width = direct2d_height = 0;
	
}

// 析构
RenderFactory::~RenderFactory() {

}

// 初始化渲染器
// RenderType_Direct2D: 窗口句柄，窗口宽度，窗口高度
void RenderFactory::InitRender(int renderType, ...) {
	auto factory_render = RenderFactory::GetInstance();
	if (factory_render) {
		// 设置渲染器类型
		factory_render->renderType = renderType;
		
		// 定义参数列表
		va_list ap;

		// 初始化参数列表
		va_start(ap, renderType);


		switch (renderType) {
		case RenderType_Direct2D:
		{
			// 获取基础参数
			HWND hWnd = va_arg(ap, HWND);
			int width = va_arg(ap, int);
			int height = va_arg(ap, int);

			// 设置渲染器参数
			factory_render->g_hWnd = hWnd;
			factory_render->direct2d_width = width;
			factory_render->direct2d_height = height;

			// 初始化
			factory_render->InitRender_Direct2D();
		}
			break;
		case RenderType_Sfml:
		{
			// 初始化
			factory_render->InitRender_SFML();
		}
			break;
		default:
			break;
		}

		// 结束参数设置
		va_end(ap);
	}
}

// 获取渲染器工厂
RenderFactory* RenderFactory::GetInstance() {
	if (!g_renderFactory) {
		g_renderFactory = new RenderFactory();
	}
	return g_renderFactory;
}

void RenderFactory::Release() {
	if (g_renderFactory) {
		delete g_renderFactory;
		g_renderFactory = nullptr;
	}
}

// 获取渲染器
Render* RenderFactory::GetRender() {
	return g_render;
}

// 初始化Diect2D类型渲染器
void RenderFactory::InitRender_Direct2D() {
	if (!g_render) {
		g_render = new Render_Direct2d();
		if (g_render) {
			auto ret = g_render->BuildRender(g_hWnd, direct2d_width, direct2d_height);
			if (ret) {
				
			}
		}
	}
}

// 初始化Sfml类型渲染器
void RenderFactory::InitRender_SFML() {
	if (!g_render) {
		
	}
}