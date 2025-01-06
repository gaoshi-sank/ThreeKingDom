#ifndef _UI_CheckBox_h_
#define _UI_CheckBox_h_

#include "UI_Button.h"
#include "UI_Contain.h"

// ��ѡ��UI
class UI_CheckBox : public UI_Contain, private UI_TriggerFunction {
private:
	std::vector<SImage*> list_image;	// ͼ���б�
	SText* _text;						// �ı�

	// �¼�����
	int check_state;					// ��ť���״̬
	int button_style;					// ��ť���
	int button_state;					// ��ť״̬
	int button_index;					// ��ť��������

public:
	// ö��ֵ
	enum CheckBoxStyle {
		CheckBoxStyle_OneOnce = 1,		// ��ť - ����Դ
		CheckBoxStyle_OneFour,			// ��ť - �����ĸ���Դ
		CheckBoxStyle_ChangeOp_Once,	// ���Ƿ��� - ����Դ 
		CheckBoxStyle_ChangeOp_Two,		// ���Ƿ��� - ����������Դ
		CheckBoxStyle_Switch,			// ���
	};


public:
	// ����
	UI_CheckBox();
	
	// ����
	~UI_CheckBox();

	// Ԥ�ͷ�
	virtual void PreRelease();

	// ����
	virtual bool Create();

	// ������ͼ�ఴť
	// ����: λ�úʹ�С
	// ����: ��Դ���4ͼ��2ͼ��
	virtual bool Create(const std::string& filename, int x = 0, int y = 0, int w = 0, int h = 0, int resStyle = 4);

	// �����ĸ�״̬ͼ��
	// ��ͨ�������ڣ����£�ʧЧ
	virtual bool Create(const std::string& out, const std::string& in, const std::string& down, const std::string& disable);

	// 

	// ���Ӿ�̬�ı�
	virtual void AddStaticText(const std::string& text);

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

	// ���õ�ѡ
	virtual void SetCheckBoxType(int _type);

	// ����������
	virtual void SetGroupId(int _id);

	// ��ȡ��ѡ״̬
	virtual bool GetCheckState();

	// ���ûص� - ��ͣ
	virtual void Event_Hover(std::function<void(int Id)> _hover);

	// ���ûص� - ����
	virtual void Event_Down(std::function<void(int Id)> _down);

	// ���ûص� - �ſ�
	virtual void Event_Up(std::function<void(int Id)> _up);

	// ���ûص� - ���
	virtual void Event_Click(std::function<void(int Id)> _hover);
};


#endif // !_UI_CheckBox_h_
