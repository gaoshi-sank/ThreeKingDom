/*
* ��̬ͼ
*/
#ifndef _UI_GIF_H_
#define _UI_GIF_H_


#include "UI_Lable.h"
#include "../../../Engine/Render/Sprite/Animation.h"

enum GIFSTYLE {
	GIFSTYLE_NONE = 0,
	GIFSTYLE_MUL,
	GIFSTYLE_SINGLE,
};

// ��̬ͼ 
class UI_GIF : public UI_Lable {
private:
	Animation* _gif;	// ֱ�Ӳ��ö�������

public:
	// ����
	UI_GIF();

	// ����
	~UI_GIF();

	// Ԥ�ͷ�
	virtual void PreRelease();

	// ����
	virtual bool Create();

	// ��������ͼ��Դ��GIF
	virtual bool Create(const std::string& filename, int rect_x, int rect_y, int rect_width, int rect_height, int cropWidth, int cropHeight, int speed);

	// �������ͼ��Դ��GIF
	virtual bool Create(std::vector<std::string> fileLists, int rect_x, int rect_y, int rect_width, int rect_height, int speed);

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
	virtual void SetVisiable(bool visible = true);
};


#endif // !_UI_GIF_H_