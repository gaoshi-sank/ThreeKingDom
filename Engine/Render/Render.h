#ifndef _Render_Direct2d_h_
#define _Render_Direct2d_h_

// 渲染包含库
#include <wincodec.h>			// WIC组件
#include <d2d1.h>				// 2d
#include <dwrite.h>				// 文字
#include <d2d1helper.h>			// ??
#include <windowsx.h>			// 获取Lparam
#include "../EngineHelper.h"	// 辅助用函数

// 渲染静态库
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"windowscodecs.lib")


// 渲染类 -- Direct2D 
class Render {
private:
	IWICImagingFactory* WicFactory = nullptr;		// WIC工厂
	ID2D1Factory* factory;							// 渲染工厂
	ID2D1HwndRenderTarget* render_target;			// 渲染画刷
	IDWriteFactory* textfactory;					// 文字工厂

	// 属性
	D2D1_COLOR_F background_color;	// 背景颜色


public:
	// 构造
	Render();

	// 析构
	virtual ~Render();

	// 创建渲染器
	virtual bool BuildRender(HWND hwnd, int width, int height);

	// 释放渲染器
	virtual void Release();

	// 开始渲染
	virtual void BeginPlay();

	// 结束渲染
	virtual void EndPlay();

	// 绘制图像
	virtual void RenderImage(
        ID2D1Bitmap* image, 
        D2D1_RECT_F rect, 
        D2D1_RECT_F src_rect, 
        float opacity = 1.0f, 
        float angle = 0.0f);

	// 绘制文本
	virtual void RenderText(
        wchar_t* render_text, 
        D2D1_RECT_F text_rect, 
        IDWriteTextLayout* layout, 
        ID2D1SolidColorBrush* brash);

    // 绘制直线
    virtual void RenderLine(
        D2D1_POINT_2F start,
        D2D1_POINT_2F end,
        D2D1_COLOR_F color,
        float strokeWidth = 1.0f,
        float angle = 0.0f,
        D2D1_POINT_2F rotationCenter = D2D1::Point2F(0, 0));

    // 绘制矩形
    virtual void RenderRectangle(
        D2D1_RECT_F rect,
        D2D1_COLOR_F fillColor,
        D2D1_COLOR_F strokeColor,
        float strokeWidth = 1.0f,
        float angle = 0.0f,
        D2D1_POINT_2F rotationCenter = D2D1::Point2F(0, 0));

    // 绘制椭圆
    virtual void RenderEllipse(
        D2D1_RECT_F rect,
        D2D1_COLOR_F fillColor,
        D2D1_COLOR_F strokeColor,
        float strokeWidth = 1.0f,
        float angle = 0.0f,
        D2D1_POINT_2F rotationCenter = D2D1::Point2F(0, 0));

    // 绘制多边形
    virtual void RenderPolygon(
        const std::vector<D2D1_POINT_2F>& points,
        D2D1_COLOR_F fillColor,
        D2D1_COLOR_F strokeColor,
        float strokeWidth = 1.0f,
        float angle = 0.0f,
        D2D1_POINT_2F rotationCenter = D2D1::Point2F(0, 0));

    // 绘制多段线
    virtual void RenderPolyline(
        const std::vector<D2D1_POINT_2F>& points,
        D2D1_COLOR_F strokeColor,
        float strokeWidth = 1.0f,
        float angle = 0.0f,
        D2D1_POINT_2F rotationCenter = D2D1::Point2F(0, 0));

	// 创建图像
	virtual ID2D1Bitmap* CreateImage(const char* filename);

	// 创建文本布局
	virtual IDWriteTextLayout* CreateTextLayout(wchar_t* render_text, IDWriteTextFormat* text_format);

	// 创建文本格式
	virtual IDWriteTextFormat* CreateTextFormat(float font_size);

	// 创建画刷
	virtual ID2D1SolidColorBrush* CreateBrush(D2D1_COLOR_F _color);

	// 设置文本风格
	virtual void SetTextStyle(IDWriteTextLayout* _layout, int horizontal, int vertical, int swrapping);

	// 保存位图到文件
	virtual bool SaveBitmapToFile(ID2D1Bitmap* pBitmap, const wchar_t* filePath);

private:
	// 获取图像格式解析对象
	HRESULT GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename);

};


#endif // !_Render_Direct2d_h_