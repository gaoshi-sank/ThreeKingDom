#include "Object_Base.h"

static unsigned int id = 0x00;

// ����
Object_Base::Object_Base() {
	this->object_id = ++id;
}

// ����
Object_Base::~Object_Base() {

}