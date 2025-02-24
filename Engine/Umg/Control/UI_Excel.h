/*
* �ĵ��б�չʾ��
*/
#ifndef _UI_Excel_H_
#define _UI_Excel_H_

#include "UI_Lable.h"

struct ExcelText {
	std::string _text;
	int rect_x, rect_y, rect_width, rect_height;

	ExcelText() {
		_text = "";
		rect_x = rect_y = rect_width = rect_height = 0;
	}
};


class UI_Excel : public UI_Lable {
private:
	std::vector<ExcelText*> list_texts;	// ��Ⱦ�ַ�
	SImage* object_background;			// ���Ʊ���
	SText* object_text;					// ���ƶ���
	int maxlength;
	bool isbuild;

public:
	// ����
	UI_Excel();

	// ����
	virtual ~UI_Excel();

public:
	// ����
	virtual bool Create();

	// ����
	// ������λ�úʹ�С
	virtual bool Create(const std::string& filename, int x, int y, int w, int h);

	// �����ַ�
	virtual void AddText(std::string _text);

	// ����λ�������ַ�
	virtual void AddText(int x, int y, std::string _text);

	// ������󳤶�
	virtual void SetMaxValue(int maxlength);

	// �豸����
	virtual void SetBackGround(const char* filename = nullptr);

	// ����������ɫ
	virtual void SetTextColor(int red, int green, int blue);

	// ���ÿɼ���
	virtual void SetVisiable(bool life = true);

	// ���� 
	virtual void Update();

	// ���� 
	virtual void Draw();

	// ����λ��
	virtual void SetLocation(int x, int y);

	// ���ô�С
	virtual void SetSize(int w, int h);
};


#endif // !_UI_Excel_H_
