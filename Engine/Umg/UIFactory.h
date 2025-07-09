#ifndef _UIFactory_h_
#define _UIFactory_h_

#include "../EngineConfig.h"
#include "Core/PlaneFactory.h"


// UI工厂
class UIFactory {
private:
	// 锁
	std::mutex lockList;
	std::mutex lockAddlist;
	std::mutex lockDellist;

	// UI列表
	std::vector<UI_Base*> list;
	std::vector<UI_Base*> addList;
	std::vector<UI_Base*> delList;

	// 构造
	UIFactory();

	// 析构
	~UIFactory();

public:
	// 初始化
	static void InitUIProvider();

	// 释放
	static void Release();

	// 添加控件
	static void AddWindow(UI_Base* _ui);

	// 删除控件
	static void DelWindow(UI_Base* _ui);

	// 事件驱动
	static void CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams);

	// 复选框事件处理
	static void CheckBoxParam(int ui_id, int group_id, int state);

	// 更新
	static void Update();

	// 渲染
	static void Draw();

	// 判断顶层
	static bool GetLevelTop(int pos_x, int pos_y, UI_Base* other);

private:

};

#endif // !_UIFactory_h_
