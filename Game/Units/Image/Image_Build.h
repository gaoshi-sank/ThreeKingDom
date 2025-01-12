#ifndef _Image_Build_h_
#define _Image_Build_h_

#include "../../../Engine/Render/Sprite/Animation.h"
#include "Image_Base.h"

class Image_Build : public Image_Base {
private:
	std::vector<std::shared_ptr<SImage>> imageList;
	int x, y, width, height;
	int buildLevel;			// �����ȼ�
	int index_back;			// ��������
	int index_front;		// ǰ������
	int index_lvlup;		// ��������


public:
	// ����
	Image_Build();

	// ����
	~Image_Build();

	// ��ʼ��
	virtual void Create(int key);

	// ��ʼ��
	virtual void Create(int key, int x, int y, int width, int height);

	// ����λ��
	virtual void SetLocation(int x,int y);

	// ���ô�С
	virtual void SetSize(int width, int height);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();

private:
	// ��������
	void SetBuildIndex(int level);

};


#endif // !_Image_Build_h_
