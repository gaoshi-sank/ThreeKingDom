#ifndef _Render_Direct2d_h_
#define _Render_Direct2d_h_

// 父类文件
#include "../Render.h"

// 渲染包含库
#include <wincodec.h>						// WIC组件
#include <d2d1.h>							// 2d
#include <dwrite.h>							// 文字
#include <d2d1helper.h>		


// 渲染静态库
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"windowscodecs.lib")


// 具体渲染类
// Direct2D API
class Render_Direct2d : public Render {
private:
	IWICImagingFactory* WicFactory = nullptr;		// WIC工厂
	ID2D1Factory* factory;							// 渲染工厂
	ID2D1HwndRenderTarget* render_target;			// 渲染画刷
	IDWriteFactory* textfactory;					// 文字工厂

	// 属性
	D2D1_COLOR_F background_color;	// 背景颜色


public:
	// 构造
	Render_Direct2d();

	// 析构
	virtual ~Render_Direct2d();

	// 创建渲染器
	virtual bool BuildRender(HWND hwnd, int width, int height);

	// 释放 渲染器
	virtual void Release();

	// 开始渲染
	virtual void BeginPlay();

	// 结束渲染
	virtual void EndPlay();

	// 绘制图像
	virtual void RenderImage(void* image, int dx = 0, int dy = 0, int dw = 0, int dh = 0, int sx = 0, int sy = 0, int sw = 0, int sh = 0, float opacity = 1.0f, float angle = 0.0f);

	// 绘制文本
	virtual void RenderText(wchar_t* render_text, int dx = 0, int dy = 0, int dw = 0, int dh = 0, void* text_layout = nullptr, void* text_brash = nullptr);

	// 创建图像
	virtual void* CreateImage(const char* filename);

	// 创建文本布局
	virtual void* CreateTextLayout(wchar_t* render_text, void* text_format);

	// 创建文本格式
	virtual void* CreateTextFormat(float font_size);

	// 创建画刷
	virtual void* CreateBrush(int red, int green, int blue, int alpha = 255);

	// 设置文本风格
	virtual void SetTextStyle(void* _layout, int horizontal, int vertical, int swrapping);

	// 获取渲染器类型
	virtual int GetType();

	// 获取图像大小
	virtual void GetImageSize(void* image, int& width, int& height);

	// 释放对象
	// 用作部分不能delete的实例
	virtual void ReleaseObject(void* _obejct);

private:
	// 获取图像格式解析对象
	HRESULT GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename);

};


#endif // !_Render_Direct2d_h_