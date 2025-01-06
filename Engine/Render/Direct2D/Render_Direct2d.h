#ifndef _Render_Direct2d_h_
#define _Render_Direct2d_h_

// �����ļ�
#include "../Render.h"

// ��Ⱦ������
#include <wincodec.h>						// WIC���
#include <d2d1.h>							// 2d
#include <dwrite.h>							// ����
#include <d2d1helper.h>		


// ��Ⱦ��̬��
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"windowscodecs.lib")


// ������Ⱦ��
// Direct2D API
class Render_Direct2d : public Render {
private:
	IWICImagingFactory* WicFactory = nullptr;		// WIC����
	ID2D1Factory* factory;							// ��Ⱦ����
	ID2D1HwndRenderTarget* render_target;			// ��Ⱦ��ˢ
	IDWriteFactory* textfactory;					// ���ֹ���

	// ����
	D2D1_COLOR_F background_color;	// ������ɫ


public:
	// ����
	Render_Direct2d();

	// ����
	virtual ~Render_Direct2d();

	// ������Ⱦ��
	virtual bool BuildRender(HWND hwnd, int width, int height);

	// �ͷ� ��Ⱦ��
	virtual void Release();

	// ��ʼ��Ⱦ
	virtual void BeginPlay();

	// ������Ⱦ
	virtual void EndPlay();

	// ����ͼ��
	virtual void RenderImage(void* image, int dx = 0, int dy = 0, int dw = 0, int dh = 0, int sx = 0, int sy = 0, int sw = 0, int sh = 0, float opacity = 1.0f, float angle = 0.0f);

	// �����ı�
	virtual void RenderText(wchar_t* render_text, int dx = 0, int dy = 0, int dw = 0, int dh = 0, void* text_layout = nullptr, void* text_brash = nullptr);

	// ����ͼ��
	virtual void* CreateImage(const char* filename);

	// �����ı�����
	virtual void* CreateTextLayout(wchar_t* render_text, void* text_format);

	// �����ı���ʽ
	virtual void* CreateTextFormat(float font_size);

	// ������ˢ
	virtual void* CreateBrush(int red, int green, int blue, int alpha = 255);

	// �����ı����
	virtual void SetTextStyle(void* _layout, int horizontal, int vertical, int swrapping);

	// ��ȡ��Ⱦ������
	virtual int GetType();

	// ��ȡͼ���С
	virtual void GetImageSize(void* image, int& width, int& height);

	// �ͷŶ���
	// �������ֲ���delete��ʵ��
	virtual void ReleaseObject(void* _obejct);

private:
	// ��ȡͼ���ʽ��������
	HRESULT GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename);

};


#endif // !_Render_Direct2d_h_