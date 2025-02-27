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
	void CreateByMul(const char* filename, int x, int y, int width, int height, int cropx = 0, int cropy = 0, int cropwidth = 0, int cropheight = 0);

	// ����
	void CreateByOne(const char* filename, int x, int y, int width, int height, int cropwidth, int cropheight);

	// ����
	void AddSprite(SImage* _newsprite);

	// ���ò���֡��
	// ֡�� = 1 ~ 120
	void SetPlaySpeed(int number);

	// ����
	virtual void Update() override;

	// ����
	virtual void Draw() override;

	// ���û���λ��
	virtual void SetLocation(int x, int y) override;

	// ���û��ƴ�С
	virtual void SetSize(int w, int h) override;

	// ������ת
	// ��δʵװ
	virtual void SetRotate(float angle) override;

	// ��ȡ����λ��
	virtual void GetLocation(int& x, int& y);

	// ��ȡ���ƴ�С
	virtual void GetSize(int& w, int& h);

	// ��ȡ��ת
	// ��δʵװ
	virtual void GetRotate(float& angle);

private:
	// ��ʱ���ص�
	void CallbackFunction();


};

#endif //!_Animation_h_