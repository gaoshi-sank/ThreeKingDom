#ifndef _PlaneFactory_h_
#define _PlaneFactory_h_

#include "UI_Plane.h"

// ���ýṹ
class PlaneSetting {
public:
	// ��������
	int uiId;				// UI�ɱ�ʶID
	int uiType;				// UI����
	int x;					// ����X��
	int y;					// ����Y��
	int width;				// ���ƿ��
	int height;				// ���Ƹ߶�
	int res;				// ��Դ��־λ
	std::string resPath;	// ��Դ·��
	int option;				// ����Plane���ǵ�������

	// ��������
	std::string lable_title;	// lable��ǩ��

	std::string button_title;	// ��ť��
	int resPath_buttonType;		// ��ť��Դ���
	std::string resPath_out, resPath_in, resPath_down, resPath_disable;

	int resPath_checkBoxType;	// ��ѡ����


	// ����
	PlaneSetting();

	// ����
	~PlaneSetting();
};




// UI������
// ��ȡUI�����ļ������������߶�ӦUI�б�
class PlaneFactory {
public:
	// �����ļ�����һ��UI_Plane
	static UI_Plane* BuildOnePlane(const char* filename);

	// �����ļ�����һϵ��UI
	static std::vector<UI_Base*> BuildUIByFile(const char* filename, std::function<void(int, int, int, int )> _callback);
};




#endif // !_PlaneFactory_h_
