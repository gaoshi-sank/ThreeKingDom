#include "Object_Base.h"

static unsigned int id = 0x00;

// ¹¹Ôì
Object_Base::Object_Base() {
	this->object_id = ++id;
}

// Îö¹¹
Object_Base::~Object_Base() {

}