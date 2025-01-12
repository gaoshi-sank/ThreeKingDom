#include "Image_Base.h"

static unsigned int id = 0x00;

// ¹¹Ôì
Image_Base::Image_Base() {
	image_id = ++id;
}

// Îö¹¹
Image_Base::~Image_Base() {

}