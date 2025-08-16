#include "Interactable.h"

#include "Application.h"
#include "Input.h"
#include "Primitives.h"

namespace IMGL {

	static Color s_button_color = DefaultButtonColor;
	static Color s_button_hover_color = DefaultButtonHoverColor;
	static Color s_button_pressed_color = DefaultButtonPressedColor;
	static Color s_button_border_color = DefaultButtonBorderColor;
	static unsigned int s_button_border_thickness = DefaultButtonBorderThickness;

	void ButtonColor(const Color& color) {
		s_button_color = color;
	}

	void ButtonHoverColor(const Color& color) {
		s_button_hover_color = color;
	}	

	void ButtonPressedColor(const Color& color) {
		s_button_pressed_color = color;
	}

	void ButtonBorder(const Color& color, unsigned int thickness) {
		s_button_border_color = color;
		s_button_border_thickness = thickness;
	}

	void DrawButton(int x, int y, int width, int height, bool& hovered, bool& pressed, bool& clicked) {
		int mx, my;
		GetMousePosition(mx, my);
		hovered = CheckRectangleBounds(x, y, width, height, mx, my);

		// Check pressed
		bool left, right, middle;
		GetMouseButton(left, right, middle);
		pressed = left && hovered;

		// Draw the button background
		if (pressed) {
			DrawRectangle(x, y, width, height, s_button_pressed_color);
		}
		else if (hovered) {
			DrawRectangle(x, y, width, height, s_button_hover_color);
		}
		else {
			DrawRectangle(x, y, width, height, s_button_color);
		}

		// Draw the button border
		if (s_button_border_thickness > 0) {
			DrawBorder(x, y, width, height, s_button_border_color, s_button_border_thickness);
		}

		MouseClick mouseClick = GetMouseClick();
		clicked = mouseClick.mouseLeftClick && CheckRectangleBounds(x, y, width, height, mx, my);
	}

}