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
	virtual void CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();

	// ����λ��
	virtual void SetRect(int x, int y, int width, int height);

	// ���ÿɼ���
	virtual void SetVisiable(bool visible = false);

};


#endif //!_UI_Lable_h_