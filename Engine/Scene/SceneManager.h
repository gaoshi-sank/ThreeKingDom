#ifndef _SceneManager_h_
#define _SceneManager_h_

#include "Scene_Base.h"

// ��������
class SceneManager {
private:
	// ����
	SceneManager();

	// ����
	~SceneManager();

	// ��ֵ̬
	static SceneManager* g_sceneManger;

	// ����
	std::map<unsigned int, Scene_Base*> MapScene;	// ��������
	unsigned int Scene_Index;						// ��������
	std::vector<unsigned int> DeleteScenes;			// ɾ������

public:
	// ��ʼ������
	static void InitSceneManager();

	// �ͷ�
	static void ReleaseScene();

	// ��ȡ����
	static SceneManager* GetInstance();

	// ����
	static void UpdateScene();

	// ����
	static void DrawScene();

	// ���볡��
	static void AddScene(Scene_Base* _scene);

	// �л�����
	static void SwitchScene(unsigned int scene_id, bool release_now = true);

	// ɾ������
	static void DeleteScene(unsigned int scene_id);

private:
	// ����
	void Update();

	// ��Ⱦ
	void Draw();

	// �ͷ�
	void Release();

};

#endif // !_SceneManager_h_
