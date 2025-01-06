#include "UI_Plane.h"

// ����
UI_Plane::UI_Plane() {
	window_style = UIStyle_Plane;
}

// ����
UI_Plane::~UI_Plane() {
	for (auto& _ui : ListAttached) {
		if (_ui && _ui->window_id != 0x00) {
			_ui->PreRelease();
			//_ui = nullptr;
		}
	}
	ListAttached.clear();
}

// Ԥ�ͷ�
void UI_Plane::PreRelease() {
	window_release = true;
}

// ����
bool UI_Plane::Create() {
	return true;
}

// ���븽��UI
void UI_Plane::AddAttachedUI(UI_Base* attached_ui) {
	if (window_release) {
		return;
	}

	bool isnewui = true;
	for (auto& _ui : ListAttached) {
		// �����ж�����
		if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
			// �����ж�����
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

// �¼�����
void UI_Plane::CheckEvent(unsigned int* param) {
	if (param) {
		for (auto& _ui : ListAttached) {
			// �����ж�����
			if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
				_ui->CheckEvent(param);
			}
		}
	}
}

// ����
void UI_Plane::Update() {
	if (window_release) {
		return;
	}

	std::mutex lockList;
	for (auto& _ui : ListAttached) {
		// �����ж�����
		if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
			_ui->Update();
		}
	}
}

// ����
void UI_Plane::Draw() {
	if (window_release) {
		return;
	}

	std::mutex lockList;
	for (auto& _ui : ListAttached) {
		// �����ж�����
		if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
			_ui->Draw();
		}
	}
}

// ����λ��
void UI_Plane::SetLocation(int x, int y) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;

}

// ���ô�С
void UI_Plane::SetSize(int w, int h) {
	if (window_release) {
		return;
	}

	this->window_width = w;
	this->window_height = h;

}

// ���ÿɼ���
void UI_Plane::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}

// ���ûص�
void UI_Plane::SetCallback(std::function<void(int uiType, int ui_id, int msgType, int message)> _callback) {
	this->callback_handle = _callback;
}

// �����¼�����
// UI���͡�UI��š���Ϣ���͡���Ϣֵ
void UI_Plane::Event_Control(int uiType, int ui_id, int msgType, int message) {
	if (this->callback_handle) {
		this->callback_handle(uiType, ui_id, msgType, message);
	}
}