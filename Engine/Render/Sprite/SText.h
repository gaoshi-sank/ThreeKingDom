#ifndef _SText_h_
#define _SText_h_

#include "BaseSprite.h"


class SText : public Sprite {
private:
	// �ı�
	std::string text;						// ����
	wchar_t* render_text;					// ��Ⱦ��
	float font_size;						// ���ִ�С
	IDWriteTextFormat* text_format;			// ���ָ�ʽ
	IDWriteTextLayout* text_layout;			// �ı����� 
	ID2D1SolidColorBrush* text_brash;		// ���ӻ�ˢ 
	D2D1_COLOR_F text_color;				// ��ˢ��ɫ

	int max_fontlength;						// �ɻ����ı�����
	int text_HorizontalStyle;				// �ı�ˮƽ��� - 1 Ĭ�Ͼ���
	int text_VerticalStyle;					// �ı���ֱ��� - 1 Ĭ�Ͼ���
	int text_swrapping;						// ���и�ʽ


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
	virtual void Draw(const std::string& render_text, D2D1_RECT_F other_rect);

	// ���û�������
	virtual void SetRect(D2D1_RECT_F _rect);

	// ������ת
	virtual void SetRotate(float angle);

	// ��ȡͼ��
	virtual ID2D1Bitmap* GetImage();

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
	void ReSetColor(D2D1_COLOR_F _color);


};



#endif // !_SText_h_