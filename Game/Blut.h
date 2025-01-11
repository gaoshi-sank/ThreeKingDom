#ifndef _Blut_h_
#define _Blut_h_

#include "../Engine/Render/Sprite/SSprite.h"

class Blut {
private:
	std::shared_ptr<Animation> test;
	
public:
	Blut();

	~Blut();

	void Init();

	void Update();

	void Draw();
};



#endif // !_Blut_h_
