#include "Blut.h"


Blut::Blut() {
	
}

Blut::~Blut() {

}

void Blut::Init() {
	test = std::make_shared<Animation>();
	if (test) {
		std::string path = "C:\\Users\\asus\\Pictures\\39\\Units\\611-1.png";
		for (auto i = 0; i < 8; i++) {
			test->AddSprite(path.c_str(), 0, 0, 0, 0, 12 * i, 0, 12, 12);
		}
		test->SetLocation(100, 100);
		test->SetSize(50, 50);
		test->SetPlaySpeed(8);
	}
}

void Blut::Update() {
	if (test) {
		int x = 0, y = 0;
		test->GetLocation(x, y);
		if (x != 0 && y != 0) {
			x += 1;
			test->SetLocation(x, y);
		}
		test->Update();
	}
}

void Blut::Draw() {
	if (test) {
		test->Draw();
	}
}