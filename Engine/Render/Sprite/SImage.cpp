#include "SImage.h"
#include "SpriteHelper.h"
#include "../RenderFactory.h"
#include "../Direct2D/Render_Direct2d.h"

// ����
SImage::SImage() {
	// ������
	draw_x = draw_y = draw_width = draw_height = 0;

	// ͼ������
	_image = nullptr;
	opacity = 1.0f;
	angle = 0.0f;
	src_x = src_y = src_width = src_height = 0;

}

// ����
SImage::SImage(const char* filename) : SImage(){
	auto render = RenderFactory::GetInstance()->GetRender();
	if (filename && render && !this->_image) {
		// ����ͼ����
		this->_image = render->CreateImage(filename);

		// Ĭ��
		render->GetImageSize(this->_image, src_width, src_height);
		draw_width = draw_x + src_width;
		draw_height = draw_y + src_height;
	}
}

// ����
SImage::~SImage() {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (_image && render) {
		render->ReleaseObject(_image);
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
			render->RenderImage(_image, draw_x, draw_y, draw_width, draw_height, src_x, src_y, src_width, src_height, opacity, angle);
		}
	}
}

// ���û���λ��
void SImage::SetLocaiton(int x, int y) {
	this->draw_x = x;
	this->draw_y = y;
}

// ���û��ƴ�С
void SImage::SetSize(int w, int h) {
	this->draw_width = w;
	this->draw_height = h;
}

// ������ת
void SImage::SetRotate(float _angle) {
	this->angle = _angle;
}

// ���òü�
void SImage::SetCrop(int x, int y, int width, int height) {
	this->src_x = x;
	this->src_y = y;
	this->src_width = width;
	this->src_height = height;
}

// ��ȡͼ���С
bool SImage::GetImageSize(int& width, int& height) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (render && _image) {
		render->GetImageSize(_image, width, height);
		return true;
	}
	return false;
}
