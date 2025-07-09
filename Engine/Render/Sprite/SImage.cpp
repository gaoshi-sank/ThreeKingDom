#include "SImage.h"
#include "../../EngineHelper.h"
#include "../RenderFactory.h"


// 构造
SImage::SImage() {
	// 图像属性
	_image = nullptr;
	opacity = 1.0f;
	angle = 0.0f;
	src_rect = D2D1::RectF();
}

// 构造
SImage::SImage(const char* filename) : SImage(){
	auto render = RenderFactory::GetInstance()->GetRender();
	if (filename && render) {
		if (!_image) {
			_image = render->CreateImage(filename);
		}

		// 默认
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

// 析构
SImage::~SImage() {
	if (_image) {
		_image->Release();
	}
	_image = nullptr;
}

// 更新
void SImage::Update() {

}

// 绘制图像
void SImage::Draw() {
	if (_image && visiable) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderImage(_image, this->draw_rect, this->src_rect, opacity, angle);
		}
	}
}

// 绘制图像 - 外部提供图像资源
void SImage::Draw(ID2D1Bitmap* other_image) {
	if (other_image) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderImage(other_image, this->draw_rect, this->src_rect, opacity, angle);
		}
	}
}

// 设置绘制区域
void SImage::SetRect(D2D1_RECT_F _rect) {
	this->draw_rect = _rect;
}

// 设置旋转
void SImage::SetRotate(float _angle) {
	this->angle = _angle;
}

// 设置裁剪区域
void SImage::SetCrop(D2D1_RECT_F cropRect) {
	this->src_rect = cropRect;
}

// 获取图像
ID2D1Bitmap* SImage::GetImage() {
	return this->_image;
}

// 获取旋转
float SImage::GetRotate() {
	return this->angle;
}

// 获取裁剪区域
D2D1_RECT_F SImage::GetCrop() {
	return this->src_rect;
}

// 保存数据
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
