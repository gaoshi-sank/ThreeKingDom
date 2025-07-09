#ifndef _Scene_Test_h_
#define _Scene_Test_h_

#include "../Engine/EngineProvider.h"


// ���Գ���
class Scene_Test : public Scene_Base {
private:
	bool isinit = false;
	int isclick = 0;

public:
	// ����
	Scene_Test();

	// ����
	virtual ~Scene_Test();

	// ��ʼ��
	virtual void Init() override;

	// �ͷ�
	virtual void Release() override;

	// ����
	virtual void Update() override;

	// ��Ⱦ
	virtual void Draw() override;

	// ֹͣ
	virtual void Stop() override;

	// �¼�����
	virtual void CheckEvent(uint32_t eventType, std::vector<uint32_t> eventParams);

	// ���UI�¼�����
	virtual void EventControl(int uiType, int ui_id, int msgType, int message);

};

#endif // !_Scene_Test_h_