/*
* 文档列表，展示条
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
	std::vector<ExcelText*> list_texts;	// 渲染字符
	SImage* object_background;			// 绘制背景
	SText* object_text;					// 绘制对象
	int maxlength;
	bool isbuild;

public:
	// 构造
	UI_Excel();

	// 析构
	virtual ~UI_Excel();

public:
	// 创建
	virtual bool Create();

	// 创建
	// 参数：位置和大小
	virtual bool Create(const std::string& filename, int x, int y, int w, int h);

	// 增加字符
	virtual void AddText(std::string _text);

	// 根据位置增加字符
	virtual void AddText(int x, int y, std::string _text);

	// 设置最大长度
	virtual void SetMaxValue(int maxlength);

	// 设备背景
	virtual void SetBackGround(const char* filename = nullptr);

	// 绘制文字颜色
	virtual void SetTextColor(int red, int green, int blue);

	// 设置可见性
	virtual void SetVisiable(bool life = true);

	// 更新 
	virtual void Update();

	// 绘制 
	virtual void Draw();

	// 设置位置
	virtual void SetLocation(int x, int y);

	// 设置大小
	virtual void SetSize(int w, int h);
};


#endif // !_UI_Excel_H_
