#include "SceneManager.h"


SceneManager* SceneManager::g_sceneManger = nullptr;

// ����
SceneManager::SceneManager() {
	// ��������
	Scene_Index = 0;		// ��������

}

// ����
SceneManager::~SceneManager() {

}


// ��ʼ������
void SceneManager::InitSceneManager() {
	// ʵ����
	auto handle = GetInstance();
	if (handle) {

	}
}

// �ͷ�
void SceneManager::ReleaseScene() {
	if (g_sceneManger) {
		g_sceneManger->Release();
	}
}

// ��ȡ����
SceneManager* SceneManager::GetInstance() {
	if (!g_sceneManger) {
		g_sceneManger = new SceneManager();
	}
	return g_sceneManger;
}

// ����
void SceneManager::UpdateScene() {
	if (g_sceneManger) {
		g_sceneManger->Update();
	}
}

// ����
void SceneManager::DrawScene() {
	if (g_sceneManger) {
		g_sceneManger->Draw();
	}
}

// ���볡��
void SceneManager::AddScene(Scene_Base* _scene) {
	if (_scene && g_sceneManger) {
		bool isnone = true;
		for (auto& mapping : g_sceneManger->MapScene) {
			auto& scene = mapping.second;
			if (scene == _scene) {
				isnone = false;
				break;
			}
		}
		if (isnone) {
			_scene->Init();											// ��ʼ��
			g_sceneManger->Scene_Index = _scene->scene_id;			// ����ӳ��
			g_sceneManger->MapScene[_scene->scene_id] = _scene;		// ����
		}
	}
}

// �л�����
void SceneManager::SwitchScene(unsigned int scene_id, bool release_now) {
	if (g_sceneManger->MapScene.count(scene_id) == 1 && scene_id != g_sceneManger->Scene_Index) {
		if (release_now) {
			DeleteScene(g_sceneManger->Scene_Index);
		}
		g_sceneManger->Scene_Index = scene_id;
	}
}

// ɾ������
void SceneManager::DeleteScene(unsigned int scene_id) {
	if (g_sceneManger->MapScene.count(scene_id) == 1) {
		// ����ɾ���б�
		g_sceneManger->MapScene[scene_id]->Stop();
		g_sceneManger->DeleteScenes.push_back(scene_id);
	}
}

// ����
void SceneManager::Update() {

	// ����ɾ���б�ɾ������
	if (!DeleteScenes.empty()) {
		std::vector<unsigned int>::iterator it;
		for (it = DeleteScenes.begin(); it != DeleteScenes.end();) {
			auto iskeep = true;
			auto id = (*it);
			if (MapScene.count(id) == 1 && MapScene[id]->isPrerelease) {
				MapScene[id]->Release();	// �����ͷ�
				delete  MapScene[id];		// �ͷ��ڴ�
				MapScene[id] = nullptr;		// �ÿ�
				MapScene.erase(id);			// ��ӳ����ɾ��
				
				// ѭ������
				iskeep = false;
				it = DeleteScenes.erase(it);
			}
			if (iskeep) {
				it++;
			}
		}
	}

	// ���� 
	if (Scene_Index != 0 && MapScene.count(Scene_Index) == 1) {
		auto& scene = MapScene[Scene_Index];
		scene->Update();
	}
}

// ��Ⱦ
void SceneManager::Draw(){
	if (Scene_Index != 0 && MapScene.count(Scene_Index) == 1) {
		auto& scene = MapScene[Scene_Index];
		scene->Draw();
	}
}

// �ͷ�
void SceneManager::Release() {

}