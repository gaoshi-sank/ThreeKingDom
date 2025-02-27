#include "Render_Sfml.h"
#include "../RenderFactory.h"

// 构造
Render_Sfml::Render_Sfml() {

}

// 析构
Render_Sfml::~Render_Sfml() {

}

// 创建渲染器
bool Render_Sfml::BuildRender(HWND hwnd, int width, int height) {
	View.create(hwnd);
	return false;
}

// 释放 渲染器
void Render_Sfml::Release() {

}

// 开始渲染
void Render_Sfml::BeginPlay() {

}

// 结束渲染
void Render_Sfml::EndPlay() {

}

// 绘制图像
void Render_Sfml::RenderImage(void* image, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, float opacity, float angle) {

}

// 绘制文本
void Render_Sfml::RenderText(wchar_t* render_text, int dx, int dy, int dw, int dh, void* text_layout, void* text_brash) {

}

// 创建图像
void* Render_Sfml::CreateImage(const char* filename) {
	sf::Texture* texture = new sf::Texture();
	if (texture && texture->loadFromFile(filename)) {
		sf::Sprite* sprite = new sf::Sprite(*texture);
		return sprite;
	}
	return nullptr;
}

// 创建文本布局
void* Render_Sfml::CreateTextLayout(wchar_t* render_text, void* text_format) {
	return nullptr;
}

// 创建文本格式
void* Render_Sfml::CreateTextFormat(float font_size) {
	return nullptr;
}

// 创建画刷
void* Render_Sfml::CreateBrush(int red, int green, int blue, int alpha) {
	return nullptr;
}

// 设置文本风格
void Render_Sfml::SetTextStyle(void* _layout, int horizontal, int vertical, int swrapping) {

}

// 获取渲染器类型
int Render_Sfml::GetType() {
	return RenderFactory::RenderType_Sfml;
}

// 获取图像大小
void Render_Sfml::GetImageSize(void* image, int& width, int& height) {

}

// 释放对象
// 用作部分不能delete的实例
void Render_Sfml::ReleaseObject(void* _obejct) {

}