#ifndef _PlaneFactory_h_
#define _PlaneFactory_h_

#include "UI_Plane.h"

// 配置结构
class PlaneSetting {
public:
	// 基础属性
	int uiId;				// UI可辨识ID
	int uiType;				// UI类型
	int x;					// 绘制X点
	int y;					// 绘制Y点
	int width;				// 绘制宽度
	int height;				// 绘制高度
	int res;				// 资源标志位
	std::string resPath;	// 资源路径
	int option;				// 生成Plane还是单独存在

	// 特殊属性
	std::string lable_title;	// lable标签用

	std::string button_title;	// 按钮用
	int resPath_buttonType;		// 按钮资源风格
	std::string resPath_out, resPath_in, resPath_down, resPath_disable;

	int resPath_checkBoxType;	// 复选框用


	// 构造
	PlaneSetting();

	// 析构
	~PlaneSetting();
};




// UI构建器
// 读取UI配置文件，生成面板或者对应UI列表
class PlaneFactory {
public:
	// 根据文件生成一个UI_Plane
	static UI_Plane* BuildOnePlane(const char* filename);

	// 根据文件生成一系列UI
	static std::vector<UI_Base*> BuildUIByFile(const char* filename, std::function<void(int, int, int, int )> _callback);
};




#endif // !_PlaneFactory_h_
