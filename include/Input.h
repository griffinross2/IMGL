#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace IMGL {

	typedef struct {
		int x;
		int y;
		bool mouseLeftClick;
		bool mouseRightClick;
		bool mouseMiddleClick;
	} MouseClick;

	void GetMousePosition(int& x, int& y);
	void GetMouseButton(bool& left, bool& right, bool& middle);

	MouseClick GetMouseClick();

    void ProcessInput();
}