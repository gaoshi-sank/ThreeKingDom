#ifndef _UI_Plane_h_
#define _UI_Plane_h_


#include "../Control/UI_Lable.h"		// ��ǩUI
#include "../Control/UI_Button.h"		// ��ťUI
#include "../Control/UI_CheckBox.h"		// ��ťUI


// �����
// һ�����ڷ�������UI�ؼ�
class UI_Plane : public UI_Base {
private:
	std::vector<UI_Base*> ListAttached;	// ����UI�б�
	std::mutex lockList;

	// �����ص�
	std::function<void(int uiType, int ui_id, int msgType, int message)> callback_handle;	

public:
	// ����
	UI_Plane();

	// ����
	virtual ~UI_Plane();

	// Ԥ�ͷ�
	virtual void PreRelease();

	// ����
	virtual bool Create();

	// ���븽��UI
	virtual void AddAttachedUI(UI_Base* _ui);

	// �¼�����
	virtual void CheckEvent(unsigned int* param);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();

	// ����λ��
	virtual void SetLocation(int x, int y);

	// ���ô�С
	virtual void SetSize(int w, int h);

	// ���ÿɼ���
	virtual void SetVisiable(bool visible = false);

	// ���ûص�
	virtual void SetCallback(std::function<void(int uiType, int ui_id, int msgType, int message)> _callback);

	// �����¼�����
	// UI���͡�UI��š���Ϣ���͡���Ϣֵ
	virtual void Event_Control(int uiType, int ui_id, int msgType, int message);

};


#endif // !_UI_Plane_h_
