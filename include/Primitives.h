#pragma once

#include "Style.h"

namespace IMGL {

    void DrawRectangle(int x, int y, int width, int height, const Color& color);
	bool CheckRectangleBounds(int x, int y, int width, int height, int pointX, int pointY);

	void DrawBorder(int x, int y, int width, int height, const Color& color, unsigned int thickness);
}