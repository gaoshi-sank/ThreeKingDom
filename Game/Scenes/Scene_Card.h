#ifndef _Scene_Card_h_
#define _Scene_Card_h_


#include "SceneInclude.h"

class Scene_Card : public Scene_Base {
private:
	std::vector<std::shared_ptr<Object_Base>> Object_List;
	bool isResInit;

public:
	// ����
	Scene_Card();

	// ����
	~Scene_Card();

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


#endif // !_Scene_Card_h_
