#ifndef _RenderFactory_h_
#define _RenderFactory_h_


#include "Render.h"


// ��Ⱦ����
class RenderFactory {
public:
	// ��Ⱦ������
	enum RenderType {
		RenderType_Direct2D = 1,	// Direct2D
	};

private:
	// ����
	RenderFactory();

	// ����
	~RenderFactory();

	// ����
	int renderType;
	Render* g_render;

	// Direct2D�ò���
	HWND g_hWnd;
	int direct2d_width, direct2d_height;

	// ��ֵ̬
	static RenderFactory* g_renderFactory;

public:
	// ��ʼ����Ⱦ��
	// RenderType_Direct2D: ���ھ�������ڿ�ȣ����ڸ߶�
	static void InitRender(int renderType, ...);

	// ��ȡ��Ⱦ������
	static RenderFactory* GetInstance();

	// �ͷ�
	static void Release();

	// ��ȡ��Ⱦ��
	Render* GetRender();

private:
	// ��ʼ��Diect2D������Ⱦ��
	void InitRender_Direct2D();

};



#endif // !_RenderFactory_h_