#include "Render_Sfml.h"
#include "../RenderFactory.h"

// ����
Render_Sfml::Render_Sfml() {

}

// ����
Render_Sfml::~Render_Sfml() {

}

// ������Ⱦ��
bool Render_Sfml::BuildRender(HWND hwnd, int width, int height) {
	View.create(hwnd);
	return false;
}

// �ͷ� ��Ⱦ��
void Render_Sfml::Release() {

}

// ��ʼ��Ⱦ
void Render_Sfml::BeginPlay() {

}

// ������Ⱦ
void Render_Sfml::EndPlay() {

}

// ����ͼ��
void Render_Sfml::RenderImage(void* image, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, float opacity, float angle) {

}

// �����ı�
void Render_Sfml::RenderText(wchar_t* render_text, int dx, int dy, int dw, int dh, void* text_layout, void* text_brash) {

}

// ����ͼ��
void* Render_Sfml::CreateImage(const char* filename) {
	sf::Texture* texture = new sf::Texture();
	if (texture && texture->loadFromFile(filename)) {
		sf::Sprite* sprite = new sf::Sprite(*texture);
		return sprite;
	}
	return nullptr;
}

// �����ı�����
void* Render_Sfml::CreateTextLayout(wchar_t* render_text, void* text_format) {
	return nullptr;
}

// �����ı���ʽ
void* Render_Sfml::CreateTextFormat(float font_size) {
	return nullptr;
}

// ������ˢ
void* Render_Sfml::CreateBrush(int red, int green, int blue, int alpha) {
	return nullptr;
}

// �����ı����
void Render_Sfml::SetTextStyle(void* _layout, int horizontal, int vertical, int swrapping) {

}

// ��ȡ��Ⱦ������
int Render_Sfml::GetType() {
	return RenderFactory::RenderType_Sfml;
}

// ��ȡͼ���С
void Render_Sfml::GetImageSize(void* image, int& width, int& height) {

}

// �ͷŶ���
// �������ֲ���delete��ʵ��
void Render_Sfml::ReleaseObject(void* _obejct) {

}