#ifndef _UI_CheckBox_h_
#define _UI_CheckBox_h_

#include "UI_Button.h"
#include "UI_Contain.h"

// 复选框UI
class UI_CheckBox : public UI_Contain, private UI_TriggerFunction {
private:
	std::vector<SImage*> list_image;	// 图像列表
	SText* _text;						// 文本

	// 事件驱动
	int check_state;					// 按钮点击状态
	int button_style;					// 按钮风格
	int button_state;					// 按钮状态
	int button_index;					// 按钮更新索引

public:
	// 枚举值
	enum CheckBoxStyle {
		CheckBoxStyle_OneOnce = 1,		// 按钮 - 单资源
		CheckBoxStyle_OneFour,			// 按钮 - 包含四个资源
		CheckBoxStyle_ChangeOp_Once,	// 三角符号 - 单资源 
		CheckBoxStyle_ChangeOp_Two,		// 三角符号 - 包含两个资源
		CheckBoxStyle_Switch,			// 框框
	};


public:
	// 构造
	UI_CheckBox();
	
	// 析构
	~UI_CheckBox();

	// 预释放
	virtual void PreRelease();

	// 创建
	virtual bool Create();

	// 创建单图类按钮
	// 参数: 位置和大小
	// 参数: 资源风格（4图和2图）
	virtual bool Create(const std::string& filename, int x = 0, int y = 0, int w = 0, int h = 0, int resStyle = 4);

	// 增加四个状态图像
	// 普通，区域内，按下，失效
	virtual bool Create(const std::string& out, const std::string& in, const std::string& down, const std::string& disable);

	// 

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

	// 设置单选
	virtual void SetCheckBoxType(int _type);

	// 设置所属组
	virtual void SetGroupId(int _id);

	// 获取单选状态
	virtual bool GetCheckState();

	// 设置回调 - 悬停
	virtual void Event_Hover(std::function<void(int Id)> _hover);

	// 设置回调 - 按下
	virtual void Event_Down(std::function<void(int Id)> _down);

	// 设置回调 - 放开
	virtual void Event_Up(std::function<void(int Id)> _up);

	// 设置回调 - 点击
	virtual void Event_Click(std::function<void(int Id)> _hover);
};


#endif // !_UI_CheckBox_h_
