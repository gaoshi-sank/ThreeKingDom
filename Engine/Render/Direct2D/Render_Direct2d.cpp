#include "Render_Direct2d.h"
#include "../RenderFactory.h"

static bool isInitCom = false;

// 多字节转为宽字符 
static bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	bool result = false;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// 转换 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}
	return result;
}

// 构造
Render_Direct2d::Render_Direct2d() {
	this->WicFactory = nullptr;			// WIC工厂
	this->factory = nullptr;			// 渲染工厂
	this->render_target = nullptr;		// 渲染画刷
	this->textfactory = nullptr;		// 文字工厂

	// 属性
	background_color = D2D1::ColorF(0, 0, 0);
}

// 析构
Render_Direct2d::~Render_Direct2d() {

}

// 构建渲染器
bool Render_Direct2d::BuildRender(HWND hWnd, int width, int height) {
	// 结果
	HRESULT hr = S_OK;

	// COM组件初始化
	if (!isInitCom) {
		hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(this->WicFactory), (LPVOID*)&(this->WicFactory));
		if (FAILED(hr)) {
			return false;
		}
		isInitCom = true;
	}

	// 创建 渲染工厂
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &(factory));
	if (FAILED(hr)) {
		return false;
	}

	// 创建 渲染画刷
	D2D1_SIZE_U Size = D2D1::SizeU(width, height);
	hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, Size), &(render_target));
	if (FAILED(hr)) {
		return false;
	}

	// 创建 文字工厂
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(textfactory), reinterpret_cast<IUnknown**>(&textfactory));
	if (FAILED(hr)) {
		return false;
	}

	// 默认返回
	return true;
}

// 释放
void Render_Direct2d::Release() {

}


// 开始渲染
void Render_Direct2d::BeginPlay() {
	if (render_target) {
		render_target->BeginDraw();
		render_target->Clear(background_color);

	}
}

// 结束渲染
void Render_Direct2d::EndPlay() {
	if (render_target) {
		render_target->EndDraw();
	}
}

// 绘制图像
void Render_Direct2d::RenderImage(void* _image, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, float opacity, float angle) {
	if (render_target && _image) {
		// 转换
		auto image = reinterpret_cast<ID2D1Bitmap*>(_image);
		auto rect = D2D1::RectF(dx * 1.0f, dy * 1.0f, dx * 1.0f + dw, dy * 1.0f + dh);
		auto src_rect = D2D1::RectF(sx * 1.0f, sy * 1.0f, sx * 1.0f + sw, sy * 1.0f + sh);

		// 绘制
		render_target->DrawBitmap(
			image, rect, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			src_rect);
	}
}

// 绘制文本
void Render_Direct2d::RenderText(wchar_t* render_text, int dx, int dy, int dw, int dh, void* layout, void* brash) {
	if (render_target && render_text && layout && brash) {
		// 转换
		auto text_rect = D2D1::RectF(dx * 1.0f, dy * 1.0f, dx * 1.0f + dw, dy * 1.0f + dh);
		auto text_layout = reinterpret_cast<IDWriteTextLayout*>(layout);
		auto text_brash = reinterpret_cast<ID2D1SolidColorBrush*>(brash);

		// 绘制
		render_target->DrawText(
			render_text, UINT32(wcslen(render_text)),
			text_layout,
			text_rect, text_brash,
			D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

// 创建图像
void* Render_Direct2d::CreateImage(const char* filename) {
	// 变量列表
	IWICFormatConverter* pConverter = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	wchar_t wfilename[260] = { 0 };
	bool result = 0;

	// 转换字符
	result = CharToWChar(filename, wfilename);
	if (result && this->render_target) {
		// 获取格式解析器
		hr = GetFormatConvert(pConverter, wfilename);

		// 由渲染器创建一个图像
		if (SUCCEEDED(hr)) {
			hr = this->render_target->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap);
			if (FAILED(hr)) {
				pBitmap->Release();
				pBitmap = nullptr;
			}
		}

		// 释放临时变量
		if (pConverter) {
			pConverter->Release();
			pConverter = nullptr;
		}
		return pBitmap;
	}
	return nullptr;
}

// 创建文本布局
void* Render_Direct2d::CreateTextLayout(wchar_t* render_text, void* _text_format) {
	IDWriteTextLayout* text_layout = nullptr;
	if (textfactory) {
		auto text_format = reinterpret_cast<IDWriteTextFormat*>(_text_format);
		textfactory->CreateTextLayout(render_text,
			UINT32(wcslen(render_text)),
			text_format,
			0, 0,
			&text_layout);
	}
	return text_layout;
}

// 创建文本格式
void* Render_Direct2d::CreateTextFormat(float font_size) {
	IDWriteTextFormat* textformat = nullptr;
	if (textfactory) {
		textfactory->CreateTextFormat(
			L"宋体", 
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			font_size,
			L"",
			&textformat);
	}
	return textformat;
}

// 创建画刷
void* Render_Direct2d::CreateBrush(int red, int green, int blue, int alpha) {
	ID2D1SolidColorBrush* color_brush = nullptr;
	if (render_target) {
		auto color = D2D1::ColorF(red * 1.0f, green * 1.0f, blue * 1.0f, alpha * 1.0f / 255);
		render_target->CreateSolidColorBrush(color, &color_brush);
	}
	return color_brush;
}

// 设置文本风格
void Render_Direct2d::SetTextStyle(void* _layout, int horizontal, int vertical, int swrapping) {
	if (_layout) {
		auto text_layout = reinterpret_cast<IDWriteTextLayout*>(_layout);
		
		// 水平
		switch (horizontal) {
		case 1: 
		{
			// 水平居中 - 默认
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		}
		case 2:
		{
			// 字体铺满区域 - 可能存在拉伸
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
			break;
		}
		case 3:	
		{
			// 水平居右
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}	
		default:
		{
			// 水平居左
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		}
		}

		// 垂直
		switch (vertical) {
		case 1: 
		{
			// 下边
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);	
			break;
		}
		case 2: 
		{
			// 上边
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		}
		default: {
			// 垂直居中 - 默认
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);	
			break;
		}
		}

		// 换行
		switch (vertical) {
		case 1: 
		{
			// 文字跨行打断，以避免文字溢出布局框
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP);
			break;
		}
		case 2: 
		{
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_EMERGENCY_BREAK); 
			break;
		}
		case 3:
		{
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_WHOLE_WORD);
			break;
		}
		case 4:
		{
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_CHARACTER);
			break;
		}
		default: {
			// 保持在同一行
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
			break;
		}
		}
	}
}

// 获取渲染器类型
int Render_Direct2d::GetType() {
	return RenderFactory::RenderType_Direct2D;
}


// 获取图像大小
void Render_Direct2d::GetImageSize(void* _image, int& width, int& height) {
	if (_image) {
		// 转换
		auto image = reinterpret_cast<ID2D1Bitmap*>(_image);	// 有风险

		// 设置属性
		auto size = image->GetSize();
		width = static_cast<int>(size.width);
		height = static_cast<int>(size.height);
	}
}

// 释放对象
// 用作部分不能delete的实例
void Render_Direct2d::ReleaseObject(void* _obejct) {
	if (_obejct) {
		auto obejct = reinterpret_cast<IUnknown*>(_obejct);
		obejct->Release();
	}
}

// 获取图像格式解析对象
HRESULT Render_Direct2d::GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename) {
	// 变量列表
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	int error = 0;								// 错误值

	// 没有错误 - 渲染对象
	if (error || !render_target || !WicFactory) {
		return -1;
	}

	// 创建图像工厂
	// 创建解码器
	hr = WicFactory->CreateDecoderFromFilename(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 获取帧数量
	UINT counter;
	if ((hr = pDecoder->GetFrameCount(&counter)) != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 获取指定帧的图像
	hr = pDecoder->GetFrame(0, &pFrame);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 创建格式
	hr = WicFactory->CreateFormatConverter(&pConverter);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 初始化格式
	hr = pConverter->Initialize(
		pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.f,
		WICBitmapPaletteTypeCustom
	);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 释放资源
buildip3:
	if (pDecoder) {
		pDecoder->Release();
		pDecoder = nullptr;
	}
	if (pFrame) {
		pFrame->Release();
		pFrame = nullptr;
	}

	if ((error != 0) || hr != S_OK) {
		return -1;
	}

	return S_OK;
}
