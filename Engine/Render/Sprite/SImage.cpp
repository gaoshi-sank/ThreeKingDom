#include "SImage.h"
#include "../../EngineHelper.h"
#include "../RenderFactory.h"


// ����
SImage::SImage() {
	// ͼ������
	_image = nullptr;
	opacity = 1.0f;
	angle = 0.0f;
	src_rect = D2D1::RectF();
}

// ����
SImage::SImage(const char* filename) : SImage(){
	auto render = RenderFactory::GetInstance()->GetRender();
	if (filename && render) {
		if (!_image) {
			_image = render->CreateImage(filename);
		}

		// Ĭ��
		if (_image) {
			auto size_f = _image->GetSize();
			src_rect.right = src_rect.left + size_f.width;
			src_rect.bottom = src_rect.top + size_f.height;
			if (draw_rect.right == 0 || draw_rect.bottom == 0) {
				draw_rect = src_rect;
			}
		}
	}
}

// ����
SImage::~SImage() {
	if (_image) {
		_image->Release();
	}
	_image = nullptr;
}

// ����
void SImage::Update() {

}

// ����ͼ��
void SImage::Draw() {
	if (_image && visiable) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderImage(_image, this->draw_rect, this->src_rect, opacity, angle);
		}
	}
}

// ����ͼ�� - �ⲿ�ṩͼ����Դ
void SImage::Draw(ID2D1Bitmap* other_image) {
	if (other_image) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderImage(other_image, this->draw_rect, this->src_rect, opacity, angle);
		}
	}
}

// ���û�������
void SImage::SetRect(D2D1_RECT_F _rect) {
	this->draw_rect = _rect;
}

// ������ת
void SImage::SetRotate(float _angle) {
	this->angle = _angle;
}

// ���òü�����
void SImage::SetCrop(D2D1_RECT_F cropRect) {
	this->src_rect = cropRect;
}

// ��ȡͼ��
ID2D1Bitmap* SImage::GetImage() {
	return this->_image;
}

// ��ȡ��ת
float SImage::GetRotate() {
	return this->angle;
}

// ��ȡ�ü�����
D2D1_RECT_F SImage::GetCrop() {
	return this->src_rect;
}

// ��������
void SImage::SaveToFile(const char* filename) {
	if (filename) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			const size_t length = strlen(filename);
			if (length > 0) {
				wchar_t* savepath = new wchar_t[length];
				if (savepath) {
					memset(savepath, 0, sizeof(wchar_t) * length);
					auto ret = CharToWChar(filename, savepath);
					if (ret) {
						render->SaveBitmapToFile(this->_image, savepath);
					}
				}
			}
		}
	}
}
