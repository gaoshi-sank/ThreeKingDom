#ifndef _UI_Base_h_
#define _UI_Base_h_

// �����ļ�
#include "../Render/Sprite/SSprite.h"	// ��Ⱦ�þ���
#include "UIHelper.h"

// �ؼ�
class UI_Base {
public:
	// ��������
	unsigned int window_id;		// ���ڱ�� 
	unsigned int window_style;	// �������� 
	bool window_visible;		// �ɼ���
	bool window_release;		// �ͷ���
	bool window_top;			// ���
	bool window_attached;		// ������
	bool window_key;			// �ɴ��������¼� 
	bool window_mouse;			// �ɴ�������¼�
	int window_renderlevel;		// ������Ⱦ��
	int window_x;				// �������� X
	int window_y;				// �������� Y
	int window_width;			// �������� width
	int window_height;			// �������� height

	// �¼�����
	int mouse_posx;				// ���X
	int mouse_posy;				// ���Y
	bool window_inrect;			// ������

public:
	// ö��ֵ
	// UI����
	enum UIStyle {
		UIStyle_Base = 0,
		UIStyle_Lable,
		UIStyle_Button,
		UIStyle_Contain,
		UIStyle_CheckBox,
		UIStyle_Plane,
		UIStyle_Excel,
	};

	// UI��Ϣ
	enum UIMsgType {
		UIMsgType_None = 0,
		UIMsgType_Hover,		// ��ͣ
		UIMsgType_Down,			// ����
		UIMsgType_Up,			// �ſ�
		UIMsgType_Click,		// ���
	};

public:
	// ����
	UI_Base();

	// ����
	virtual ~UI_Base();

	// Ԥ�ͷ�
	virtual void PreRelease() = 0;

	// ����
	virtual bool Create() = 0;

	// �¼�����
	virtual void CheckEvent(unsigned int* param) = 0;

	// ����
	virtual void Update() = 0;

	// ����
	virtual void Draw() = 0;

	// ����λ��
	virtual void SetLocation(int x, int y) = 0;

	// ���ô�С
	virtual void SetSize(int w, int h) = 0;

	// ���ÿɼ���
	virtual void SetVisiable(bool visible = false) = 0;
};


#endif //!_UI_Base_h_