#include "UI_Base.h"
#include "UIFactory.h"

static unsigned int baseid = 0x00;

// ����
UI_Base::UI_Base() {
	// ��������
	this->window_id = ++baseid;				// ���ڱ�� 
	this->window_style = UIStyle_Base;		// �������� 
	this->window_visible = true;			// Ĭ�� - �ɼ�
	this->window_release = false;			// Ĭ�� - δ�ͷ�
	this->window_top = false;				// Ĭ�� - ��Ͳ�
	this->window_attached = false;			// Ĭ�� - �����ؼ�
	this->window_key = false;				// Ĭ�� - ���������� 
	this->window_mouse = true;				// Ĭ�� - �ɴ������ 
	this->window_renderlevel = 0x00;		// Ĭ�� - ��Ⱦ�� 0

	// �¼�����
	mouse_posx = mouse_posy = 0;
	window_inrect = false;
	
	// ��������
	this->window_x = this->window_y = this->window_width = this->window_height = 0;

	// �������
	UIFactory::AddWindow(this);
}

// ����
UI_Base::~UI_Base() {

}

// �����¼�
void UI_Base::CheckEvent(unsigned int* param) {
	if (window_release || !param) {
		return;
	}

	int param_len = param[0];
	if (param_len >= 2) {
		auto message = param[1];

		// �������λ��
		if (window_mouse && message == WM_MOUSEMOVE) {
			// Ĭ�ϲ��ڴ���
			window_inrect = false;	

			// ��ȷ��ȡ
			if (param_len >= 3) {
				LPARAM lParam = (LPARAM)param[2];
				mouse_posx = GET_X_LPARAM(lParam);
				mouse_posy = GET_Y_LPARAM(lParam);

				// �ж϶���
				window_top = UIFactory::GetLevelTop(mouse_posx, mouse_posy, this);

				// �ж�������
				if (window_top && Point_In_Rect(mouse_posx, mouse_posy, window_x, window_y, window_width, window_height)) {
					window_inrect = true;
				}
			}
		}
	}
}