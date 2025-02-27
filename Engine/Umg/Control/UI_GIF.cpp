#include "UI_GIF.h"


// ���� 
UI_GIF::UI_GIF() {
	// �������� 
	this->window_style = UI_Base::UIStyle_Gif;
	_gif = nullptr;
}

// ����
UI_GIF::~UI_GIF() {

}

// �ͷ�
void UI_GIF::PreRelease() {
	
}

// ����
bool UI_GIF::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// ��������ͼ��Դ��GIF
bool UI_GIF::Create(const std::string& filename, int rect_x, int rect_y, int rect_width, int rect_height, int cropWidth, int cropHeight, int speed) {
	if (!_gif) {
		_gif = new Animation();
		if (_gif) {
			_gif->CreateByOne(filename.c_str(), rect_x, rect_y, rect_width, rect_height, cropWidth, cropHeight);
			_gif->SetPlaySpeed(speed);
		}
	}
	return Create();
}

// �������ͼ��Դ��GIF
bool UI_GIF::Create(std::vector<std::string> fileLists, int rect_x, int rect_y, int rect_width, int rect_height, int speed) {
	if (!_gif) {
		_gif = new Animation();
		if (_gif) {
			for (auto& filename : fileLists) {
				if (!filename.empty()) {
					_gif->CreateByMul(filename.c_str(), rect_x, rect_y, rect_width, rect_height);
				}
			}
			_gif->SetPlaySpeed(speed);
		}
	}
	return Create();
}

// �����¼�
void UI_GIF::CheckEvent(unsigned int* param) {

}

// ����
void UI_GIF::Update() {
	if (window_release) {
		return;
	}

	if (_gif) {
		_gif->Update();
	}
}

// ��Ⱦ
void UI_GIF::Draw() {
	if (_gif) {
		_gif->Draw();
	}
}

// ����λ��
void UI_GIF::SetLocation(int x, int y) {
	if (window_release) {
		return;
	}
	this->window_x = x;
	this->window_y = y;

}

// ���ô�С
void UI_GIF::SetSize(int w, int h) {
	if (window_release) {
		return;
	}
	this->window_width = w;
	this->window_height = h;
}

// ���ÿɼ���
void UI_GIF::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}
	this->window_visible = visible;
}