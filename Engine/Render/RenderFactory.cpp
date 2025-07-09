#include "RenderFactory.h"
#include <Windows.h>

// ��Ⱦ����
static RenderFactory* g_renderFactory = nullptr;;

// ����
RenderFactory::RenderFactory() {
	m_hWnd = nullptr;
	m_render = std::make_shared<Render>();
	m_height = m_width = 0;
}

// ����
RenderFactory::~RenderFactory() {
	// �Զ�����
}

// ��ʼ����Ⱦ��
void RenderFactory::InitRender(HWND hWnd, int width, int height) {
	auto factory_render = RenderFactory::GetInstance();
	if (factory_render) {
		// ��ʼ��
		factory_render->m_hWnd = hWnd;
		factory_render->m_width = width;
		factory_render->m_height = height;
		factory_render->LoadRender();
	}
}

// ��ȡ��Ⱦ������
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

// ��ȡ��Ⱦ��
std::shared_ptr<Render> RenderFactory::GetRender() {
	return m_render;
}


// ������Ⱦ��
void RenderFactory::LoadRender() {
	if (m_render) {
		m_render->BuildRender(m_hWnd, m_width, m_height);
	}
}
