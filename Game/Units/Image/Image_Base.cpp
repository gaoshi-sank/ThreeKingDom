#include "Image_Base.h"

static unsigned int id = 0x00;

// ����
Image_Base::Image_Base() {
	image_id = ++id;
}

// ����
Image_Base::~Image_Base() {

}