#ifndef _Scene_Test_h_
#define _Scene_Test_h_


#include "../../Engine/Scene/SceneManager.h"
#include "../../Engine/Log/LogSystem.h"
#include "../Units/Object_Army.h"
#include "../Units/Object_Build.h"
#include "../Units/Object_Hero.h"


class Scene_Test : public Scene_Base {
private:
	std::vector<std::shared_ptr<Object_Base>> Object_List;

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
