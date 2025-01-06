#include "SceneManager.h"


SceneManager* SceneManager::g_sceneManger = nullptr;

// 构造
SceneManager::SceneManager() {
	// 基础属性
	Scene_Index = 0;		// 场景索引

}

// 析构
SceneManager::~SceneManager() {

}


// 初始化引擎
void SceneManager::InitSceneManager() {
	// 实例化
	auto handle = GetInstance();
	if (handle) {

	}
}

// 释放
void SceneManager::ReleaseScene() {
	if (g_sceneManger) {
		g_sceneManger->Release();
	}
}

// 获取引擎
SceneManager* SceneManager::GetInstance() {
	if (!g_sceneManger) {
		g_sceneManger = new SceneManager();
	}
	return g_sceneManger;
}

// 更新
void SceneManager::UpdateScene() {
	if (g_sceneManger) {
		g_sceneManger->Update();
	}
}

// 绘制
void SceneManager::DrawScene() {
	if (g_sceneManger) {
		g_sceneManger->Draw();
	}
}

// 加入场景
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
			_scene->Init();											// 初始化
			g_sceneManger->Scene_Index = _scene->scene_id;			// 加入映射
			g_sceneManger->MapScene[_scene->scene_id] = _scene;		// 保存
		}
	}
}

// 切换场景
void SceneManager::SwitchScene(unsigned int scene_id, bool release_now) {
	if (g_sceneManger->MapScene.count(scene_id) == 1 && scene_id != g_sceneManger->Scene_Index) {
		if (release_now) {
			DeleteScene(g_sceneManger->Scene_Index);
		}
		g_sceneManger->Scene_Index = scene_id;
	}
}

// 删除场景
void SceneManager::DeleteScene(unsigned int scene_id) {
	if (g_sceneManger->MapScene.count(scene_id) == 1) {
		// 加入删除列表
		g_sceneManger->MapScene[scene_id]->Stop();
		g_sceneManger->DeleteScenes.push_back(scene_id);
	}
}

// 更新
void SceneManager::Update() {

	// 根据删除列表删除场景
	if (!DeleteScenes.empty()) {
		std::vector<unsigned int>::iterator it;
		for (it = DeleteScenes.begin(); it != DeleteScenes.end();) {
			auto iskeep = true;
			auto id = (*it);
			if (MapScene.count(id) == 1 && MapScene[id]->isPrerelease) {
				MapScene[id]->Release();	// 场景释放
				delete  MapScene[id];		// 释放内存
				MapScene[id] = nullptr;		// 置空
				MapScene.erase(id);			// 从映射中删除
				
				// 循环条件
				iskeep = false;
				it = DeleteScenes.erase(it);
			}
			if (iskeep) {
				it++;
			}
		}
	}

	// 更新 
	if (Scene_Index != 0 && MapScene.count(Scene_Index) == 1) {
		auto& scene = MapScene[Scene_Index];
		scene->Update();
	}
}

// 渲染
void SceneManager::Draw(){
	if (Scene_Index != 0 && MapScene.count(Scene_Index) == 1) {
		auto& scene = MapScene[Scene_Index];
		scene->Draw();
	}
}

// 释放
void SceneManager::Release() {

}