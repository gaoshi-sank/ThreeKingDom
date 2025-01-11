#ifndef _Unit_h_
#define _Unit_h_

#include "Blut.h"

class Unit {
private:
	std::shared_ptr<Animation> _image;	// Í¼Ïñ



public:
	Unit();

	~Unit();

	void CreateUnit(int x, int y);

	void Update();

	void Draw();


};



#endif // !_Unit_h_

