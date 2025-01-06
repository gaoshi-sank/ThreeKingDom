#ifndef _Animation_h_
#define _Animation_h_

#include "SImage.h"
#include "../../Timer/TimerFactory.h"

// ������
class Animation {
private:
	std::vector<SImage*> ListSprite;
	int showIndex;
	Timer* _timer;

public:
	// ����
	Animation();

	// ����
	~Animation();

	// ����
	void AddSprite(const char* filename, int x, int y, int width, int height, int cropx, int cropy, int cropwidth, int cropheight);

	// ����
	void AddSprite(SImage* _newsprite);

	// ���ò���֡��
	// ֡�� = 1 ~ 120
	void SetPlaySpeed(int number);

	// ����
	void Update();

	// ����
	void Draw();

private:
	// ��ʱ���ص�
	void CallbackFunction();


};

#endif //!_Animation_h_