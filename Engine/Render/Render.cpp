#include "Render.h"
#include "RenderFactory.h"

static bool isInitCom = false;

// ����
Render::Render() {
	this->WicFactory = nullptr;			// WIC����
	this->factory = nullptr;			// ��Ⱦ����
	this->render_target = nullptr;		// ��Ⱦ��ˢ
	this->textfactory = nullptr;		// ���ֹ���

	// ����
	background_color = D2D1::ColorF(0, 0, 0);
}

// ����
Render::~Render() {

}

// ������Ⱦ��
bool Render::BuildRender(HWND hWnd, int width, int height) {
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
void Render::Release() {

}

// ��ʼ��Ⱦ
void Render::BeginPlay() {
	if (render_target) {
		render_target->BeginDraw();
		render_target->Clear(background_color);

	}
}

// ������Ⱦ
void Render::EndPlay() {
	if (render_target) {
		render_target->EndDraw();
	}
}

// ����ͼ��
void Render::RenderImage(ID2D1Bitmap* image, D2D1_RECT_F rect, D2D1_RECT_F src_rect, float opacity, float angle) {
	if (render_target && image) {
		//  ����һ��״̬�飨���������ͼ״̬��
		ID2D1DrawingStateBlock* pStateBlock = nullptr;
		factory->CreateDrawingStateBlock(&pStateBlock);

		if (pStateBlock) {
			// ���浱ǰ��ͼ״̬
			render_target->SaveDrawingState(pStateBlock);

			// ����ͼƬ���ĵ�
			D2D1_POINT_2F center = D2D1::Point2F(
				(rect.left + rect.right) / 2,
				(rect.top + rect.bottom) / 2
			);

			// ������ת��angle����ת�Ƕȣ�
			render_target->SetTransform(
				D2D1::Matrix3x2F::Rotation(angle, center)
			);

			// ����ͼƬ
			render_target->DrawBitmap(image, rect, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src_rect);

			// �ָ���ͼ״̬
			render_target->RestoreDrawingState(pStateBlock);

			// �ͷ�
			pStateBlock->Release();
		}

		pStateBlock = nullptr;
	}
}

// �����ı�
void Render::RenderText(wchar_t* render_text, D2D1_RECT_F text_rect, IDWriteTextLayout* layout, ID2D1SolidColorBrush* brash) {
	if (render_target && render_text && layout && brash) {
		render_target->DrawText(render_text, UINT32(wcslen(render_text)), layout, text_rect, brash, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

// ����ֱ��
void Render::RenderLine(D2D1_POINT_2F start, D2D1_POINT_2F end,
	D2D1_COLOR_F color, float strokeWidth,
	float angle, D2D1_POINT_2F rotationCenter) {
	if (!render_target) return;

	ID2D1SolidColorBrush* pBrush = nullptr;
	render_target->CreateSolidColorBrush(color, &pBrush);
	if (!pBrush) return;

	// ���浱ǰ��ͼ״̬
	ID2D1DrawingStateBlock* pStateBlock = nullptr;
	factory->CreateDrawingStateBlock(&pStateBlock);
	if (pStateBlock) {
		render_target->SaveDrawingState(pStateBlock);

		// ������ת
		if (angle != 0.0f) {
			render_target->SetTransform(
				D2D1::Matrix3x2F::Rotation(angle, rotationCenter)
			);
		}

		// ����ֱ��
		render_target->DrawLine(start, end, pBrush, strokeWidth);

		// �ָ���ͼ״̬
		render_target->RestoreDrawingState(pStateBlock);
		pStateBlock->Release();
	}

	pBrush->Release();
}

// ���ƾ���
void Render::RenderRectangle(D2D1_RECT_F rect, D2D1_COLOR_F fillColor,
	D2D1_COLOR_F strokeColor, float strokeWidth,
	float angle, D2D1_POINT_2F rotationCenter) {
	if (!render_target) return;

	ID2D1SolidColorBrush* pFillBrush = nullptr;
	ID2D1SolidColorBrush* pStrokeBrush = nullptr;
	render_target->CreateSolidColorBrush(fillColor, &pFillBrush);
	render_target->CreateSolidColorBrush(strokeColor, &pStrokeBrush);
	if (!pFillBrush || !pStrokeBrush) {
		if (pFillBrush) pFillBrush->Release();
		if (pStrokeBrush) pStrokeBrush->Release();
		return;
	}

	// ���浱ǰ��ͼ״̬
	ID2D1DrawingStateBlock* pStateBlock = nullptr;
	factory->CreateDrawingStateBlock(&pStateBlock);
	if (pStateBlock) {
		render_target->SaveDrawingState(pStateBlock);

		// ������ת
		if (angle != 0.0f) {
			render_target->SetTransform(
				D2D1::Matrix3x2F::Rotation(angle, rotationCenter)
			);
		}

		// ������
		render_target->FillRectangle(rect, pFillBrush);
		// ���ƾ��α߿�
		render_target->DrawRectangle(rect, pStrokeBrush, strokeWidth);

		// �ָ���ͼ״̬
		render_target->RestoreDrawingState(pStateBlock);
		pStateBlock->Release();
	}

	pFillBrush->Release();
	pStrokeBrush->Release();
}

// ������Բ
void Render::RenderEllipse(D2D1_RECT_F rect, D2D1_COLOR_F fillColor,
	D2D1_COLOR_F strokeColor, float strokeWidth,
	float angle, D2D1_POINT_2F rotationCenter) {
	if (!render_target) return;

	ID2D1SolidColorBrush* pFillBrush = nullptr;
	ID2D1SolidColorBrush* pStrokeBrush = nullptr;
	render_target->CreateSolidColorBrush(fillColor, &pFillBrush);
	render_target->CreateSolidColorBrush(strokeColor, &pStrokeBrush);
	if (!pFillBrush || !pStrokeBrush) {
		if (pFillBrush) pFillBrush->Release();
		if (pStrokeBrush) pStrokeBrush->Release();
		return;
	}

	// ������Բ������
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(
		D2D1::Point2F((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2),
		(rect.right - rect.left) / 2,
		(rect.bottom - rect.top) / 2
	);

	// ���浱ǰ��ͼ״̬
	ID2D1DrawingStateBlock* pStateBlock = nullptr;
	factory->CreateDrawingStateBlock(&pStateBlock);
	if (pStateBlock) {
		render_target->SaveDrawingState(pStateBlock);

		// ������ת
		if (angle != 0.0f) {
			render_target->SetTransform(
				D2D1::Matrix3x2F::Rotation(angle, rotationCenter)
			);
		}

		// �����Բ
		render_target->FillEllipse(ellipse, pFillBrush);
		// ������Բ�߿�
		render_target->DrawEllipse(ellipse, pStrokeBrush, strokeWidth);

		// �ָ���ͼ״̬
		render_target->RestoreDrawingState(pStateBlock);
		pStateBlock->Release();
	}

	pFillBrush->Release();
	pStrokeBrush->Release();
}

// ���ƶ����
void Render::RenderPolygon(const std::vector<D2D1_POINT_2F>& points,
	D2D1_COLOR_F fillColor, D2D1_COLOR_F strokeColor,
	float strokeWidth, float angle,
	D2D1_POINT_2F rotationCenter) {
	if (!render_target || points.size() < 3) return;

	ID2D1SolidColorBrush* pFillBrush = nullptr;
	ID2D1SolidColorBrush* pStrokeBrush = nullptr;
	render_target->CreateSolidColorBrush(fillColor, &pFillBrush);
	render_target->CreateSolidColorBrush(strokeColor, &pStrokeBrush);
	if (!pFillBrush || !pStrokeBrush) {
		if (pFillBrush) pFillBrush->Release();
		if (pStrokeBrush) pStrokeBrush->Release();
		return;
	}

	// ����·��������
	ID2D1PathGeometry* pPathGeometry = nullptr;
	factory->CreatePathGeometry(&pPathGeometry);
	if (!pPathGeometry) {
		pFillBrush->Release();
		pStrokeBrush->Release();
		return;
	}

	// ���ƶ����·��
	ID2D1GeometrySink* pSink = nullptr;
	pPathGeometry->Open(&pSink);
	if (pSink) {
		pSink->BeginFigure(points[0], D2D1_FIGURE_BEGIN_FILLED);
		for (size_t i = 1; i < points.size(); ++i) {
			pSink->AddLine(points[i]);
		}
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		pSink->Close();
		pSink->Release();
	}

	// ���浱ǰ��ͼ״̬
	ID2D1DrawingStateBlock* pStateBlock = nullptr;
	factory->CreateDrawingStateBlock(&pStateBlock);
	if (pStateBlock) {
		render_target->SaveDrawingState(pStateBlock);

		// ������ת
		if (angle != 0.0f) {
			render_target->SetTransform(
				D2D1::Matrix3x2F::Rotation(angle, rotationCenter)
			);
		}

		// �������
		render_target->FillGeometry(pPathGeometry, pFillBrush);
		// ���ƶ���α߿�
		render_target->DrawGeometry(pPathGeometry, pStrokeBrush, strokeWidth);

		// �ָ���ͼ״̬
		render_target->RestoreDrawingState(pStateBlock);
		pStateBlock->Release();
	}

	pPathGeometry->Release();
	pFillBrush->Release();
	pStrokeBrush->Release();
}

// ���ƶ����
void Render::RenderPolyline(const std::vector<D2D1_POINT_2F>& points,
	D2D1_COLOR_F strokeColor, float strokeWidth,
	float angle, D2D1_POINT_2F rotationCenter) {
	if (!render_target || points.size() < 2) return;

	ID2D1SolidColorBrush* pStrokeBrush = nullptr;
	render_target->CreateSolidColorBrush(strokeColor, &pStrokeBrush);
	if (!pStrokeBrush) return;

	// ����·��������
	ID2D1PathGeometry* pPathGeometry = nullptr;
	factory->CreatePathGeometry(&pPathGeometry);
	if (!pPathGeometry) {
		pStrokeBrush->Release();
		return;
	}

	// ���ƶ����·��
	ID2D1GeometrySink* pSink = nullptr;
	pPathGeometry->Open(&pSink);
	if (pSink) {
		pSink->BeginFigure(points[0], D2D1_FIGURE_BEGIN_HOLLOW);
		for (size_t i = 1; i < points.size(); ++i) {
			pSink->AddLine(points[i]);
		}
		pSink->EndFigure(D2D1_FIGURE_END_OPEN);
		pSink->Close();
		pSink->Release();
	}

	// ���浱ǰ��ͼ״̬
	ID2D1DrawingStateBlock* pStateBlock = nullptr;
	factory->CreateDrawingStateBlock(&pStateBlock);
	if (pStateBlock) {
		render_target->SaveDrawingState(pStateBlock);

		// ������ת
		if (angle != 0.0f) {
			render_target->SetTransform(
				D2D1::Matrix3x2F::Rotation(angle, rotationCenter)
			);
		}

		// ���ƶ����
		render_target->DrawGeometry(pPathGeometry, pStrokeBrush, strokeWidth);

		// �ָ���ͼ״̬
		render_target->RestoreDrawingState(pStateBlock);
		pStateBlock->Release();
	}

	pPathGeometry->Release();
	pStrokeBrush->Release();
}

// ����ͼ��
ID2D1Bitmap* Render::CreateImage(const char* filename) {
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
IDWriteTextLayout* Render::CreateTextLayout(wchar_t* render_text, IDWriteTextFormat* text_format) {
	IDWriteTextLayout* _layout = nullptr;
	if (textfactory) {
		textfactory->CreateTextLayout(render_text,
			UINT32(wcslen(render_text)),
			text_format,
			0, 0,
			&_layout);
	}
	return _layout;
}

// �����ı���ʽ
IDWriteTextFormat* Render::CreateTextFormat(float font_size) {
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
ID2D1SolidColorBrush* Render::CreateBrush(D2D1_COLOR_F _color) {
	ID2D1SolidColorBrush* color_brush = nullptr;
	if (render_target) {
		render_target->CreateSolidColorBrush(_color, &color_brush);
	}
	return color_brush;
}

// �����ı����
void Render::SetTextStyle(IDWriteTextLayout* _layout, int horizontal, int vertical, int swrapping) {
	if (_layout) {
		// ˮƽ
		switch (horizontal) {
		case 1: 
		{
			// ˮƽ���� - Ĭ��
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		}
		case 2:
		{
			// ������������ - ���ܴ�������
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
			break;
		}
		case 3:	
		{
			// ˮƽ����
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}	
		default:
		{
			// ˮƽ����
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		}
		}

		// ��ֱ
		switch (vertical) {
		case 1: 
		{
			// �±�
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);	
			break;
		}
		case 2: 
		{
			// �ϱ�
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		}
		default: {
			// ��ֱ���� - Ĭ��
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);	
			break;
		}
		}

		// ����
		switch (vertical) {
		case 1: 
		{
			// ���ֿ��д�ϣ��Ա�������������ֿ�
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP);
			break;
		}
		case 2: 
		{
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_EMERGENCY_BREAK); 
			break;
		}
		case 3:
		{
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_WHOLE_WORD);
			break;
		}
		case 4:
		{
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_CHARACTER);
			break;
		}
		default: {
			// ������ͬһ��
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
			break;
		}
		}
	}
}

// ����λͼ���ļ�
bool Render::SaveBitmapToFile(ID2D1Bitmap* pBitmap, const wchar_t* filePath) {
	return false;
}
// ��ȡͼ���ʽ��������
HRESULT Render::GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename) {
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
