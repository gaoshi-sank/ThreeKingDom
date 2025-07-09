#ifndef _Animation_h_
#define _Animation_h_

#include "SImage.h"
#include "../../Timer/TimerFactory.h"

// ������
class Animation : public Sprite {
private:
	std::vector<SImage*> ListSprite;
	bool sameSprite;
	int showIndex;
	Timer* _timer;

public:
	// ����
	Animation();

	// ����
	virtual ~Animation();

	// ����
	void CreateByMul(const char* filename, D2D1_RECT_F drawRect, D2D1_RECT_F cropRect);

	// ����
	void CreateByOne(const char* filename, D2D1_RECT_F drawRect, D2D1_RECT_F cropRect);

	// ����
	void AddSprite(SImage* _newsprite);

	// ���ò���֡��
	// ֡�� = 1 ~ 120
	void SetPlaySpeed(int number);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();

	// ���û�������
	virtual void SetRect(D2D1_RECT_F _rect);

	// ������ת
	virtual void SetRotate(float angle);

	// ��ȡͼ��
	virtual ID2D1Bitmap* GetImage();

private:
	// ��ʱ���ص�
	void CallbackFunction();


};

#endif //!_Animation_h_