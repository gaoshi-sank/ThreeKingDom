#include "UI_Plane.h"

// 构造
UI_Plane::UI_Plane() {
	window_style = UIStyle_Plane;
}

// 析构
UI_Plane::~UI_Plane() {
	for (auto& _ui : ListAttached) {
		if (_ui && _ui->window_id != 0x00) {
			_ui->PreRelease();
			//_ui = nullptr;
		}
	}
	ListAttached.clear();
}

// 预释放
void UI_Plane::PreRelease() {
	window_release = true;
}

// 创建
bool UI_Plane::Create() {
	return true;
}

// 加入附属UI
void UI_Plane::AddAttachedUI(UI_Base* attached_ui) {
	if (window_release) {
		return;
	}

	bool isnewui = true;
	for (auto& _ui : ListAttached) {
		// 基础判断条件
		if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
			// 附加判断条件
			if (_ui == attached_ui || _ui->window_id == attached_ui->window_id) {
				isnewui = false;
				break;
			}
		}
	}

	if(isnewui){
		std::mutex lockList;
		attached_ui->window_attached = true;
		ListAttached.push_back(attached_ui);
	}
}

// 事件驱动
void UI_Plane::CheckEvent(unsigned int* param) {
	if (param) {
		for (auto& _ui : ListAttached) {
			// 基础判断条件
			if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
				_ui->CheckEvent(param);
			}
		}
	}
}

// 更新
void UI_Plane::Update() {
	if (window_release) {
		return;
	}

	std::mutex lockList;
	for (auto& _ui : ListAttached) {
		// 基础判断条件
		if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
			_ui->Update();
		}
	}
}

// 绘制
void UI_Plane::Draw() {
	if (window_release) {
		return;
	}

	std::mutex lockList;
	for (auto& _ui : ListAttached) {
		// 基础判断条件
		if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
			_ui->Draw();
		}
	}
}

// 设置位置
void UI_Plane::SetLocation(int x, int y) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;

}

// 设置大小
void UI_Plane::SetSize(int w, int h) {
	if (window_release) {
		return;
	}

	this->window_width = w;
	this->window_height = h;

}

// 设置可见性
void UI_Plane::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}

// 设置回调
void UI_Plane::SetCallback(std::function<void(int uiType, int ui_id, int msgType, int message)> _callback) {
	this->callback_handle = _callback;
}

// 触发事件处理
// UI类型、UI编号、消息类型、消息值
void UI_Plane::Event_Control(int uiType, int ui_id, int msgType, int message) {
	if (this->callback_handle) {
		this->callback_handle(uiType, ui_id, msgType, message);
	}
}