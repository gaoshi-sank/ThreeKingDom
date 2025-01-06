#ifndef _Render_h_
#define _Render_h_

#include <Windows.h>
#include <Windowsx.h>
#include "../EngineConfig.h"


// ������Ⱦ��
class Render {
public:
	// Ĭ�Ϲ��������
	Render() = default;
	virtual ~Render() = default;

	// ������Ⱦ��
	virtual bool BuildRender(HWND hwnd, int width, int height) = 0;
	
	// �ͷ���Ⱦ��
	virtual void Release() = 0;

	// ��ʼ��Ⱦ
	virtual void BeginPlay() = 0;

	// ������Ⱦ
	virtual void EndPlay() = 0;

	// ����ͼ��
	virtual void RenderImage(void* image, int dx = 0, int dy = 0, int dw = 0, int dh = 0, int sx = 0, int sy = 0, int sw = 0, int sh = 0, float opacity = 1.0f, float angle = 0.0f) = 0;

	// �����ı�
	virtual void RenderText(wchar_t* render_text, int dx = 0, int dy = 0, int dw = 0, int dh = 0, void* text_layout = nullptr, void* text_brash = nullptr) = 0;

	// ����ͼ��
	virtual void* CreateImage(const char* filename) = 0;

	// �����ı�

	// �����ı�����
	virtual void* CreateTextLayout(wchar_t* render_text, void* text_format) = 0;

	// �����ı���ʽ
	virtual void* CreateTextFormat(float font_size) = 0;

	// ������ˢ
	virtual void* CreateBrush(int red, int green, int blue, int alpha = 255) = 0;

	// �����ı����
	virtual void SetTextStyle(void* text_layout, int horizontal, int vertical, int swrapping ) = 0;

	// ��ȡ��Ⱦ������
	virtual int GetType() = 0;

	// ��ȡͼ���С
	virtual void GetImageSize(void* image, int& width, int& height) = 0;

	// �ͷŶ���
	// �������ֲ���delete��ʵ��
	virtual void ReleaseObject(void* _obejct) = 0;

};

#endif // !_Render_h_


