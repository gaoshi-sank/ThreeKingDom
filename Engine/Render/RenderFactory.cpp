#include "RenderFactory.h"
#include "Direct2D/Render_Direct2d.h"
#include <stdarg.h>

RenderFactory* RenderFactory::g_renderFactory = nullptr;;


// ����
RenderFactory::RenderFactory() {
	renderType = RenderType_Direct2D;
	g_render = nullptr;

	// Direct2d��Ⱦ�����Ͳ���
	g_hWnd = nullptr;
	direct2d_width = direct2d_height = 0;
	
}

// ����
RenderFactory::~RenderFactory() {

}

// ��ʼ����Ⱦ��
// RenderType_Direct2D: ���ھ�������ڿ�ȣ����ڸ߶�
void RenderFactory::InitRender(int renderType, ...) {
	auto factory_render = RenderFactory::GetInstance();
	if (factory_render) {
		// ������Ⱦ������
		factory_render->renderType = renderType;
		
		// ��������б�
		va_list ap;

		// ��ʼ�������б�
		va_start(ap, renderType);


		switch (renderType) {
		case RenderType_Direct2D:
		{
			// ��ȡ��������
			HWND hWnd = va_arg(ap, HWND);
			int width = va_arg(ap, int);
			int height = va_arg(ap, int);

			// ������Ⱦ������
			factory_render->g_hWnd = hWnd;
			factory_render->direct2d_width = width;
			factory_render->direct2d_height = height;

			// ��ʼ��
			factory_render->InitRender_Direct2D();
		}
			break;
		case RenderType_Sfml:
		{
			// ��ʼ��
			factory_render->InitRender_SFML();
		}
			break;
		default:
			break;
		}

		// ������������
		va_end(ap);
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
Render* RenderFactory::GetRender() {
	return g_render;
}

// ��ʼ��Diect2D������Ⱦ��
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

// ��ʼ��Sfml������Ⱦ��
void RenderFactory::InitRender_SFML() {
	if (!g_render) {
		
	}
}