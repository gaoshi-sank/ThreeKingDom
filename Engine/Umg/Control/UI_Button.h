#ifndef _UI_Button_h_
#define _UI_Button_h_


#include "UI_Lable.h"

// ��ťUI
class UI_Button : public UI_Lable, private UI_TriggerFunction {
private:
	std::vector<SImage*> list_image;	// ͼ���б�
	SText* _text;						// �ı�

	// �¼�����
	int click_state;			// ��ť���״̬
	int button_style;			// ��ť���
	int button_state;			// ��ť״̬
	int button_index;			// ��ť��������

public:
	// ö��ֵ
	enum ButtonStyle {
		ButtonStyle_Once = 1,	// һ��ͼ���4����ť״̬
		ButtonStyle_Four,
	};

public:
	// ����
	UI_Button();

	// ����
	~UI_Button();

	// Ԥ�ͷ�
	virtual void PreRelease();

	// ����
	virtual bool Create();

	// ������ͼ�ఴť�������ĸ�״̬��ͼ��
	// ������λ�úʹ�С
	virtual bool Create(const std::string& filename, int x, int y, int w, int h);

	// �����ĸ�״̬ͼ��
	// ��ͨ�������ڣ����£�ʧЧ
	virtual bool Create(const std::string& out, const std::string& in, const std::string& down, const std::string& disable);

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

	// ���ûص� - ��ͣ
	virtual void Event_Hover(std::function<void(int Id)> _hover);

	// ���ûص� - ����
	virtual void Event_Down(std::function<void(int Id)> _down);

	// ���ûص� - �ſ�
	virtual void Event_Up(std::function<void(int Id)> _up);

	// ���ûص� - ���
	virtual void Event_Click(std::function<void(int Id)> _hover);
};


#endif // !_UI_Button_h_


