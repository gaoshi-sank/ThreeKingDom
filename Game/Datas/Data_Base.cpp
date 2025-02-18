#include "Data_Base.h"

static unsigned int id = 0x00;

Data_Base::Data_Base() {
	dataId = ++id;
}

Data_Base::~Data_Base() {

}

