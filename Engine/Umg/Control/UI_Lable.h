#ifndef _UI_Lable_h_
#define _UI_Lable_h_

#include "../UI_Base.h"
#include "UI_TriggerFunction.h"

// ��ǩUI
class UI_Lable : public UI_Base {
private:
	SImage* _image;	// ͼ��
	SText* _text;	// �ı�

public:
	// ����
	UI_Lable();

	// ����
	~UI_Lable();

	// Ԥ�ͷ�
	virtual void PreRelease();

	// ����
	virtual bool Create();

	// ����ͼ�� 
	// ������λ�úʹ�С
	virtual bool Create(const std::string& filename, int x, int y, int w, int h);

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

};


#endif //!_UI_Lable_h_