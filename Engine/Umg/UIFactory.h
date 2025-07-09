#ifndef _UIFactory_h_
#define _UIFactory_h_

#include "../EngineConfig.h"
#include "Core/PlaneFactory.h"


// UI����
class UIFactory {
private:
	// ��
	std::mutex lockList;
	std::mutex lockAddlist;
	std::mutex lockDellist;

	// UI�б�
	std::vector<UI_Base*> list;
	std::vector<UI_Base*> addList;
	std::vector<UI_Base*> delList;

	// ����
	UIFactory();

	// ����
	~UIFactory();

public:
	// ��ʼ��
	static void InitUIProvider();

	// �ͷ�
	static void Release();

	// ��ӿؼ�
	static void AddWindow(UI_Base* _ui);

	// ɾ���ؼ�
	static void DelWindow(UI_Base* _ui);

	// �¼�����
	static void CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams);

	// ��ѡ���¼�����
	static void CheckBoxParam(int ui_id, int group_id, int state);

	// ����
	static void Update();

	// ��Ⱦ
	static void Draw();

	// �ж϶���
	static bool GetLevelTop(int pos_x, int pos_y, UI_Base* other);

private:

};

#endif // !_UIFactory_h_
