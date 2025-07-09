#ifndef _RenderFactory_h_
#define _RenderFactory_h_

#include <iostream>
#include <memory>
#include "Render.h"


// 渲染工厂
class RenderFactory {
private:
	// 构造
	RenderFactory();

	// 析构
	~RenderFactory();

	// 属性
	HWND m_hWnd;
	int32_t m_width, m_height;
	std::shared_ptr<Render> m_render;

public:
	// 初始化渲染器
	static void InitRender(HWND hWnd, int width, int height);

	// 获取渲染器工厂
	static RenderFactory* GetInstance();

	// 释放
	static void Release();

	// 获取渲染器
	std::shared_ptr<Render> GetRender();

private:
	// 加载渲染器
	void LoadRender();

};



#endif // !_RenderFactory_h_