#ifndef _Scene_Base_h_
#define _Scene_Base_h_

#include "../EngineConfig.h"

// ���������� - ������
// ��Ҫ���� - ��ʼ�����ͷš����¡����ơ�ֹͣ
class Scene_Base {
public:
	unsigned int scene_id;
	bool isPrerelease;

public:
	// ����
	Scene_Base();

	// ����
	virtual ~Scene_Base();

	// ��ʼ��
	virtual void Init() = 0;

	// �ͷ�
	virtual void Release() = 0;

	// ����
	virtual void Update() = 0;

	// ��Ⱦ
	virtual void Draw() = 0;

	// ֹͣ
	virtual void Stop() = 0;
};

#endif // !_Scene_Base_h_
