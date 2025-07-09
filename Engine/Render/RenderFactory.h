#ifndef _RenderFactory_h_
#define _RenderFactory_h_

#include <iostream>
#include <memory>
#include "Render.h"


// ��Ⱦ����
class RenderFactory {
private:
	// ����
	RenderFactory();

	// ����
	~RenderFactory();

	// ����
	HWND m_hWnd;
	int32_t m_width, m_height;
	std::shared_ptr<Render> m_render;

public:
	// ��ʼ����Ⱦ��
	static void InitRender(HWND hWnd, int width, int height);

	// ��ȡ��Ⱦ������
	static RenderFactory* GetInstance();

	// �ͷ�
	static void Release();

	// ��ȡ��Ⱦ��
	std::shared_ptr<Render> GetRender();

private:
	// ������Ⱦ��
	void LoadRender();

};



#endif // !_RenderFactory_h_