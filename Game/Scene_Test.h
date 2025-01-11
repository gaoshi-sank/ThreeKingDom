#ifndef _Scene_Test_h_
#define _Scene_Test_h_


#include "../Engine/Scene/SceneManager.h"
#include "Unit.h"

class Scene_Test : public Scene_Base {
private:
	std::shared_ptr<Blut> test;
	std::vector<std::shared_ptr<Unit>> unitsList;

public:
	// ����
	Scene_Test();

	// ����
	~Scene_Test();

	// ��ʼ��
	virtual void Init();

	// �ͷ�
	virtual void Release();

	// ����
	virtual void Update();

	// ��Ⱦ
	virtual void Draw();

	// ֹͣ
	virtual void Stop();
};


#endif // !1
