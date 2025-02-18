/*
* �ӿڶ���
*	���ڻ��ƻ���
*/
#ifndef _CameraView_H_
#define _CameraView_H_

#include "../../Engine/Render/RenderFactory.h"

// �ṹ�� - ��ͼ�ӿ�
class CameraView {
public:
	int rect_x, rect_y,
		rect_width, rect_height;	// ��Ұ����
	float width, height;			// ��ȣ��߶�

public:
	// ����
	CameraView();

	// ����
	// ���� - �ӿڴ�С
	CameraView(int rect_x, int rect_y, int rect_width, int rect_height);

	// ����
	~CameraView();

	// ����
	void Update(int face, float step);
};

#endif // !_CameraView_H_
