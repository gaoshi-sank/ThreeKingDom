#ifndef _UI_Button_h_
#define _UI_Button_h_


#include "UI_Lable.h"

// 按钮UI
class UI_Button : public UI_Lable, private UI_TriggerFunction {
private:
	std::vector<SImage*> list_image;	// 图像列表
	SText* _text;						// 文本

	// 事件驱动
	int click_state;			// 按钮点击状态
	int button_style;			// 按钮风格
	int button_state;			// 按钮状态
	int button_index;			// 按钮更新索引

public:
	// 枚举值
	enum ButtonStyle {
		ButtonStyle_Once = 1,	// 一个图完成4个按钮状态
		ButtonStyle_Four,
	};

public:
	// 构造
	UI_Button();

	// 析构
	~UI_Button();

	// 预释放
	virtual void PreRelease();

	// 创建
	virtual bool Create();

	// 创建单图类按钮（包含四个状态的图像）
	// 参数：位置和大小
	virtual bool Create(const std::string& filename, int x, int y, int w, int h);

	// 增加四个状态图像
	// 普通，区域内，按下，失效
	virtual bool Create(const std::string& out, const std::string& in, const std::string& down, const std::string& disable);

	// 增加静态文本
	virtual void AddStaticText(const std::string& text);

	// 事件驱动
	virtual void CheckEvent(unsigned int* param);

	// 更新
	virtual void Update();

	// 绘制
	virtual void Draw();

	// 设置位置
	virtual void SetLocation(int x, int y);

	// 设置大小
	virtual void SetSize(int w, int h);

	// 设置可见性
	virtual void SetVisiable(bool visible = false);

	// 设置回调 - 悬停
	virtual void Event_Hover(std::function<void(int Id)> _hover);

	// 设置回调 - 按下
	virtual void Event_Down(std::function<void(int Id)> _down);

	// 设置回调 - 放开
	virtual void Event_Up(std::function<void(int Id)> _up);

	// 设置回调 - 点击
	virtual void Event_Click(std::function<void(int Id)> _hover);
};


#endif // !_UI_Button_h_


