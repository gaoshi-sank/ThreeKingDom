#include "Render_Direct2d.h"
#include "../RenderFactory.h"

static bool isInitCom = false;

// ���ֽ�תΪ���ַ� 
static bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	bool result = false;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// ת�� 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}
	return result;
}

// ����
Render_Direct2d::Render_Direct2d() {
	this->WicFactory = nullptr;			// WIC����
	this->factory = nullptr;			// ��Ⱦ����
	this->render_target = nullptr;		// ��Ⱦ��ˢ
	this->textfactory = nullptr;		// ���ֹ���

	// ����
	background_color = D2D1::ColorF(0, 0, 0);
}

// ����
Render_Direct2d::~Render_Direct2d() {

}

// ������Ⱦ��
bool Render_Direct2d::BuildRender(HWND hWnd, int width, int height) {
	// ���
	HRESULT hr = S_OK;

	// COM�����ʼ��
	if (!isInitCom) {
		hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(this->WicFactory), (LPVOID*)&(this->WicFactory));
		if (FAILED(hr)) {
			return false;
		}
		isInitCom = true;
	}

	// ���� ��Ⱦ����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &(factory));
	if (FAILED(hr)) {
		return false;
	}

	// ���� ��Ⱦ��ˢ
	D2D1_SIZE_U Size = D2D1::SizeU(width, height);
	hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, Size), &(render_target));
	if (FAILED(hr)) {
		return false;
	}

	// ���� ���ֹ���
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(textfactory), reinterpret_cast<IUnknown**>(&textfactory));
	if (FAILED(hr)) {
		return false;
	}

	// Ĭ�Ϸ���
	return true;
}

// �ͷ�
void Render_Direct2d::Release() {

}


// ��ʼ��Ⱦ
void Render_Direct2d::BeginPlay() {
	if (render_target) {
		render_target->BeginDraw();
		render_target->Clear(background_color);

	}
}

// ������Ⱦ
void Render_Direct2d::EndPlay() {
	if (render_target) {
		render_target->EndDraw();
	}
}

// ����ͼ��
void Render_Direct2d::RenderImage(void* _image, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, float opacity, float angle) {
	if (render_target && _image) {
		// ת��
		auto image = reinterpret_cast<ID2D1Bitmap*>(_image);
		auto rect = D2D1::RectF(dx * 1.0f, dy * 1.0f, dx * 1.0f + dw, dy * 1.0f + dh);
		auto src_rect = D2D1::RectF(sx * 1.0f, sy * 1.0f, sx * 1.0f + sw, sy * 1.0f + sh);

		// ����
		render_target->DrawBitmap(
			image, rect, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			src_rect);
	}
}

// �����ı�
void Render_Direct2d::RenderText(wchar_t* render_text, int dx, int dy, int dw, int dh, void* layout, void* brash) {
	if (render_target && render_text && layout && brash) {
		// ת��
		auto text_rect = D2D1::RectF(dx * 1.0f, dy * 1.0f, dx * 1.0f + dw, dy * 1.0f + dh);
		auto text_layout = reinterpret_cast<IDWriteTextLayout*>(layout);
		auto text_brash = reinterpret_cast<ID2D1SolidColorBrush*>(brash);

		// ����
		render_target->DrawText(
			render_text, UINT32(wcslen(render_text)),
			text_layout,
			text_rect, text_brash,
			D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

// ����ͼ��
void* Render_Direct2d::CreateImage(const char* filename) {
	// �����б�
	IWICFormatConverter* pConverter = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	wchar_t wfilename[260] = { 0 };
	bool result = 0;

	// ת���ַ�
	result = CharToWChar(filename, wfilename);
	if (result && this->render_target) {
		// ��ȡ��ʽ������
		hr = GetFormatConvert(pConverter, wfilename);

		// ����Ⱦ������һ��ͼ��
		if (SUCCEEDED(hr)) {
			hr = this->render_target->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap);
			if (FAILED(hr)) {
				pBitmap->Release();
				pBitmap = nullptr;
			}
		}

		// �ͷ���ʱ����
		if (pConverter) {
			pConverter->Release();
			pConverter = nullptr;
		}
		return pBitmap;
	}
	return nullptr;
}

// �����ı�����
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

// �����ı���ʽ
void* Render_Direct2d::CreateTextFormat(float font_size) {
	IDWriteTextFormat* textformat = nullptr;
	if (textfactory) {
		textfactory->CreateTextFormat(
			L"����", 
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

// ������ˢ
void* Render_Direct2d::CreateBrush(int red, int green, int blue, int alpha) {
	ID2D1SolidColorBrush* color_brush = nullptr;
	if (render_target) {
		auto color = D2D1::ColorF(red * 1.0f, green * 1.0f, blue * 1.0f, alpha * 1.0f / 255);
		render_target->CreateSolidColorBrush(color, &color_brush);
	}
	return color_brush;
}

// �����ı����
void Render_Direct2d::SetTextStyle(void* _layout, int horizontal, int vertical, int swrapping) {
	if (_layout) {
		auto text_layout = reinterpret_cast<IDWriteTextLayout*>(_layout);
		
		// ˮƽ
		switch (horizontal) {
		case 1: 
		{
			// ˮƽ���� - Ĭ��
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		}
		case 2:
		{
			// ������������ - ���ܴ�������
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
			break;
		}
		case 3:	
		{
			// ˮƽ����
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}	
		default:
		{
			// ˮƽ����
			text_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		}
		}

		// ��ֱ
		switch (vertical) {
		case 1: 
		{
			// �±�
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);	
			break;
		}
		case 2: 
		{
			// �ϱ�
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		}
		default: {
			// ��ֱ���� - Ĭ��
			text_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);	
			break;
		}
		}

		// ����
		switch (vertical) {
		case 1: 
		{
			// ���ֿ��д�ϣ��Ա�������������ֿ�
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
			// ������ͬһ��
			text_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
			break;
		}
		}
	}
}

// ��ȡ��Ⱦ������
int Render_Direct2d::GetType() {
	return RenderFactory::RenderType_Direct2D;
}


// ��ȡͼ���С
void Render_Direct2d::GetImageSize(void* _image, int& width, int& height) {
	if (_image) {
		// ת��
		auto image = reinterpret_cast<ID2D1Bitmap*>(_image);	// �з���

		// ��������
		auto size = image->GetSize();
		width = static_cast<int>(size.width);
		height = static_cast<int>(size.height);
	}
}

// �ͷŶ���
// �������ֲ���delete��ʵ��
void Render_Direct2d::ReleaseObject(void* _obejct) {
	if (_obejct) {
		auto obejct = reinterpret_cast<IUnknown*>(_obejct);
		obejct->Release();
	}
}

// ��ȡͼ���ʽ��������
HRESULT Render_Direct2d::GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename) {
	// �����б�
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	int error = 0;								// ����ֵ

	// û�д��� - ��Ⱦ����
	if (error || !render_target || !WicFactory) {
		return -1;
	}

	// ����ͼ�񹤳�
	// ����������
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

	// ��ȡ֡����
	UINT counter;
	if ((hr = pDecoder->GetFrameCount(&counter)) != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// ��ȡָ��֡��ͼ��
	hr = pDecoder->GetFrame(0, &pFrame);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// ������ʽ
	hr = WicFactory->CreateFormatConverter(&pConverter);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// ��ʼ����ʽ
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

	// �ͷ���Դ
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
