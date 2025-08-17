#pragma once

#include "Style.h"

#include <string>

namespace IMGL {
	
	void ButtonColor(const Color& color);
	void ButtonHoverColor(const Color& color);
	void ButtonPressedColor(const Color& color);
	void ButtonBorder(const Color& color, unsigned int thickness);
	void DrawButton(const std::string& text, int x, int y, int width, int height, bool& hovered, bool& pressed, bool& clicked);

}