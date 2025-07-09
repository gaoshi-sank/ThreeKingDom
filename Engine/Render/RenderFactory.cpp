#include "RenderFactory.h"
#include <Windows.h>

// 渲染工厂
static RenderFactory* g_renderFactory = nullptr;;

// 构造
RenderFactory::RenderFactory() {
	m_hWnd = nullptr;
	m_render = std::make_shared<Render>();
	m_height = m_width = 0;
}

// 析构
RenderFactory::~RenderFactory() {
	// 自动析构
}

// 初始化渲染器
void RenderFactory::InitRender(HWND hWnd, int width, int height) {
	auto factory_render = RenderFactory::GetInstance();
	if (factory_render) {
		// 初始化
		factory_render->m_hWnd = hWnd;
		factory_render->m_width = width;
		factory_render->m_height = height;
		factory_render->LoadRender();
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
std::shared_ptr<Render> RenderFactory::GetRender() {
	return m_render;
}


// 加载渲染器
void RenderFactory::LoadRender() {
	if (m_render) {
		m_render->BuildRender(m_hWnd, m_width, m_height);
	}
}
