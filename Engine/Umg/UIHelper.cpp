#include "UIHelper.h"

// ÅÐ¶¨ pos ÔÚ (x, y, width, height)
bool Point_In_Rect(int posx, int posy, int x, int y, int width, int height) {
	if (x <= posx && posx <= (x + width)) {
		if (y <= posy && posy <= (y + height)) {
			return true;
		}
	}
	return false;
}