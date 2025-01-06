#ifndef _SceneManager_h_
#define _SceneManager_h_

#include "Scene_Base.h"

// 场景管理
class SceneManager {
private:
	// 构造
	SceneManager();

	// 析构
	~SceneManager();

	// 静态值
	static SceneManager* g_sceneManger;

	// 属性
	std::map<unsigned int, Scene_Base*> MapScene;	// 场景集合
	unsigned int Scene_Index;						// 场景索引
	std::vector<unsigned int> DeleteScenes;			// 删除场景

public:
	// 初始化引擎
	static void InitSceneManager();

	// 释放
	static void ReleaseScene();

	// 获取引擎
	static SceneManager* GetInstance();

	// 更新
	static void UpdateScene();

	// 绘制
	static void DrawScene();

	// 加入场景
	static void AddScene(Scene_Base* _scene);

	// 切换场景
	static void SwitchScene(unsigned int scene_id, bool release_now = true);

	// 删除场景
	static void DeleteScene(unsigned int scene_id);

private:
	// 更新
	void Update();

	// 渲染
	void Draw();

	// 释放
	void Release();

};

#endif // !_SceneManager_h_
