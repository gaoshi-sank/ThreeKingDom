#include "Image_Army.h"


// ����
Image_Army::Image_Army() {
	face_Index = 0x00;
	x = y = width = height = 0;
}

// ����
Image_Army::~Image_Army() {

}

// ��ʼ��
void Image_Army::Create(int key) {
	auto dataPro = DataProvider::GetInstance();
	if (dataPro) {
		// ��ȡ·��
		auto reslist = dataPro->GetUnitPath(key);

		// ��������
		int index = 0;
		int faces[] = { 9, 6, 3, 2, 1, 4, 7, 8 };
		for (auto& resnode : reslist) {
			auto _image = std::make_shared<Animation>();
			if (_image) {
				for (auto i = 0; i < 8; i++) {
					_image->AddSprite(resnode.path.c_str(), 0, 0, 0, 0, resnode.width * i, 0, resnode.width, resnode.height);
				}
				_image->SetPlaySpeed(8);
			}
			face_mapping[faces[index++]] = _image;
		}

		// ����Ĭ�ϳ���
		face_Index = 6;
	}
}

// ��ʼ��
void Image_Army::Create(int key, int x, int y, int width, int height) {
	Create(key);
	SetLocation(x, y);
	SetSize(width, height);
}

// ����λ��
void Image_Army::SetLocation(int x, int y) {
	this->x = x;
	this->y = y;
	for (auto& key_value : face_mapping) {
		auto& face_Image = key_value.second;
		if (face_Image) {
			face_Image->SetLocation(x, y);
		}
	}
}

// ���ô�С
void Image_Army::SetSize(int width, int height) {
	this->width = width;
	this->height = height;
	for (auto& key_value : face_mapping) {
		auto& face_Image = key_value.second;
		if (face_Image) {
			face_Image->SetSize(width, height);
		}
	}
}

// ���ó���
void Image_Army::SetFace(int face) {
	if (face != 8 && face >= 1 && face <= 9) {
		this->face_Index = face;
	}
	else {
		this->face_Index = 6;	// Ĭ�ϳ���
	}
}

// ����
void Image_Army::Update() {
	if (face_Index != 0x00 && face_mapping.count(face_Index) == 1) {
		auto& anmation = face_mapping[face_Index];
		anmation->Update();
	}
}

// ����
void Image_Army::Draw() {
	if (face_Index != 0x00 && face_mapping.count(face_Index) == 1) {
		auto& anmation = face_mapping[face_Index];
		anmation->Draw();
	}
}

