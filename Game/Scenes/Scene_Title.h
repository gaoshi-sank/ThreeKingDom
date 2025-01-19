#ifndef _Scene_Title_h_
#define _Scene_Title_h_


#include "SceneInclude.h"

class Scene_Title : public Scene_Base {
private:
	std::shared_ptr<SText> _object;

public:
	// ����
	Scene_Title();

	// ����
	~Scene_Title();

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


#endif // !_Scene_Title_h_
