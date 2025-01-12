#include "Image_Build.h"


// 构造
Image_Build::Image_Build() {
	x = y = width = height = 0;
	buildLevel = 0;
	index_back = 0;
	index_front = 0;
	index_lvlup = 0;

}

// 析构
Image_Build::~Image_Build() {

}

// 初始化
void Image_Build::Create(int key) {
	auto dataPro = DataProvider::GetInstance();
	if (dataPro) {
		// 获取路径
		auto reslist = dataPro->GetBuildPath(key);

		// 生成图像
		for (auto& node : reslist) {
			auto newimage = std::make_shared<SImage>(node.path.c_str());
			imageList.push_back(newimage);
		}

		// 默认等级0
		buildLevel = 0;
		SetBuildIndex(buildLevel);
	}
}

// 初始化
void Image_Build::Create(int key, int x, int y, int width, int height) {
	Create(key);
	SetLocation(x, y);
	SetSize(width, height);

	// 设置内部位置
	auto index = 0;
	for (auto& image : imageList) {
		++index;
		if (image) {
			if (index >= 5 && index <= 8) {
				int img_x = -1;
				int img_y = -1;
				image->GetLocation(img_x, img_y);
				if (img_x != -1 && img_y != -1) {
					img_y += (int)(height * 0.4012);		// 偏移
					image->SetLocation(img_x, img_y);
				}
			}
		}
	}

}

// 设置位置
void Image_Build::SetLocation(int x, int y) {
	this->x = x;
	this->y = y;
	for (auto& image : imageList) {
		if (image) {
			image->SetLocation(x, y);
		}
	}
}

// 设置大小
void Image_Build::SetSize(int width, int height) {
	this->width = width;
	this->height = height;
	for (auto& image : imageList) {
		if (image) {
			image->SetSize(width, height);
		}
	}
}



// 更新
void Image_Build::Update() {
	// 背景
	if (index_back - 1 >= 0 && index_back - 1 < (int)imageList.size()) {
		imageList[index_back - 1]->Update();
	}

	// 内饰
	if (index_lvlup - 1 >= 0 && index_lvlup - 1 < (int)imageList.size()) {
		imageList[index_lvlup - 1]->Update();
	}

	// 前景
	if (index_front - 1 >= 0 && index_front - 1 < (int)imageList.size()) {
		imageList[index_front - 1]->Update();
	}
}

// 绘制
void Image_Build::Draw() {
	// 背景
	if (index_back - 1 >= 0 && index_back - 1 < (int)imageList.size()) {
		imageList[index_back - 1]->Draw();
	}

	// 内饰
	if (index_lvlup - 1 >= 0 && index_lvlup - 1 < (int)imageList.size()) {
		imageList[index_lvlup - 1]->Draw();
	}

	// 前景
	if (index_front - 1 >= 0 && index_front - 1 < (int)imageList.size()) {
		imageList[index_front - 1]->Draw();
	}
}

void Image_Build::SetBuildIndex(int level) {
	if (level > 0) {
		if (level == 5) {
			index_back = 4;
			index_front = 8;
			index_lvlup = 11;
		}
		else if (level == 4) {
			index_back = 3;
			index_front = 7;
			index_lvlup = 11;
		}
		else if (level == 3) {
			index_back = 2;
			index_front = 6;
			index_lvlup = 10;
		}
		else if (level == 2) {
			index_back = 1;
			index_front = 5;
			index_lvlup = 9;
		}
		else if (level == 1) {
			index_back = 1;
			index_front = 5;
			index_lvlup = 0;
		}
	}
	else {
		index_back = 4;
		index_front = 8;
		index_lvlup = 0;
	}
}
