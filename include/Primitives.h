#pragma once

#include "Style.h"

namespace IMGL {

    void DrawRectangle(int x, int y, int width, int height, const Color& color);
	void DrawBorder(int x, int y, int width, int height, const Color& color, unsigned int thickness);
}