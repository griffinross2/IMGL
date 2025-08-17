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

	void AddKeyEventCallback(void func(int key, int action, int mod));
	void AddCharEventCallback(void func(unsigned int codepoint));

	void KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CharEventCallback(GLFWwindow* window, unsigned int codepoint);
    void ProcessInput();
}