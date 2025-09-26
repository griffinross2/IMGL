#pragma once

#include "Style.h"

namespace IMGL {

    void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color);
    void DrawRectangle(int x, int y, int width, int height, const Color& color);
	bool CheckRectangleBounds(int x, int y, int width, int height, int pointX, int pointY);
	bool CheckRectangleBoundsGlobal(int x, int y, int width, int height, int pointX, int pointY);

	void DrawLine(int x1, int y1, int x2, int y2, const Color& color, unsigned int thickness);

	void DrawBorder(int x, int y, int width, int height, const Color& color, unsigned int thickness);
}