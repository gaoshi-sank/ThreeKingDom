#ifndef _Image_Army_h_
#define _Image_Army_h_


#include "Image_Base.h"

class Image_Army : public Image_Base {
private:
	std::map<int, std::shared_ptr<Animation>> face_mapping;
	int face_Index;
	int x, y, width, height;

public:
	// ����
	Image_Army();

	// ����
	~Image_Army();

	// ��ʼ��
	virtual void Create(int key);

	// ��ʼ��
	virtual void Create(int key, int x, int y, int width, int height);

	// ����λ��
	virtual void SetLocation(int x,int y);

	// ���ô�С
	virtual void SetSize(int width, int height);

	// ���ó���
	virtual void SetFace(int face);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();


};


#endif // !_Image_Army_h_
