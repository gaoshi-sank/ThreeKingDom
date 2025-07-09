#ifndef _Scene_Base_h_
#define _Scene_Base_h_

#include "../EngineConfig.h"

// ���������� - ������
// ��Ҫ���� - ��ʼ�����ͷš����¡����ơ�ֹͣ
class Scene_Base {
public:
	unsigned int scene_id;
	int scene_type;
	bool isPrerelease;
	std::function<void(int*)> trigger_scene;

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

	// �¼�����
	virtual void CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams) = 0;

	// �ص�����
	virtual void Callback(std::function<void(int*)> _callback);
};

#endif // !_Scene_Base_h_
