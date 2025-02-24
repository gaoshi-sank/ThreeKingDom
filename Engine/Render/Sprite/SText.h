#ifndef _SText_h_
#define _SText_h_

#include "BaseSprite.h"


class SText : public Sprite {
private:
	// �ı�
	std::string text;			// ����
	wchar_t* render_text;		// ��Ⱦ��
	float font_size;			// ���ִ�С
	void* text_format;			// ���ָ�ʽ
	void* text_layout;			// �ı����� 
	void* text_brash;			// ���ӻ�ˢ 
	int text_color[3];			// ��ˢ��ɫ
	int max_fontlength;			// �ɻ����ı�����
	int text_HorizontalStyle;	// �ı�ˮƽ��� - 1 Ĭ�Ͼ���
	int text_VerticalStyle;		// �ı���ֱ��� - 1 Ĭ�Ͼ���
	int text_swrapping;			// ���и�ʽ


public:
	// ����
	SText();

	// ����
	SText(const char* _text);

	// ����
	~SText();

	// ����
	virtual void Update();

	// �����ı�
	virtual void Draw();

	// �����ı�
	virtual void Draw(const std::string& render_text, int dx, int dy, int dw, int dh);

	// ���û���λ��
	virtual void SetLocation(int x, int y);

	// ���û��ƴ�С
	virtual void SetSize(int w, int h);

	// ������ת 
	// ��δʵװ
	virtual void SetRotate(float angle);

	// ��ȡ����λ��
	virtual void GetLocation(int& x, int& y);

	// ��ȡ���ƴ�С
	virtual void GetSize(int& w, int& h);

	// ��ȡ��ת
	// ��δʵװ
	virtual void GetRotate(float& angle);

	// ���貼�� 
	// ˮƽ��ʽ: ����
	// ��ֱ��ʽ: ����
	// �Զ�����: ����ͬһ�� 
	void ReSetLayout(int level_Style = 1, int vertical_Style = 0, int swrapping = 1);

	// �����ı�
	void ReSetText(const char* text = nullptr);

	// ���������С 
	void ReSetFont(float font_size = 18.0f);

	// ������ɫ 
	void ReSetColor(int red, int green, int blue);


};



#endif // !_SText_h_