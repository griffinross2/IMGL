#pragma once

#include <memory>
#include <functional>

#include "Container.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace IMGL {

	typedef enum {
		CURSOR_ARROW = GLFW_ARROW_CURSOR,
		CURSOR_POINTING_HAND = GLFW_POINTING_HAND_CURSOR,
		CURSOR_IBEAM = GLFW_IBEAM_CURSOR,
		CURSOR_CROSSHAIR = GLFW_CROSSHAIR_CURSOR,
		CURSOR_EW_RESIZE = GLFW_RESIZE_EW_CURSOR,
		CURSOR_NS_RESIZE = GLFW_RESIZE_NS_CURSOR,
		CURSOR_NWSE_RESIZE = GLFW_RESIZE_NWSE_CURSOR,
		CURSOR_NESW_RESIZE = GLFW_RESIZE_NESW_CURSOR,
		CURSOR_RESIZE_ALL = GLFW_RESIZE_ALL_CURSOR,
		CURSOR_NOT_ALLOWED = GLFW_NOT_ALLOWED_CURSOR,
	} CursorShape;

	typedef struct {
		int x;
		int y;
		bool mouseLeftClick;
		bool mouseRightClick;
		bool mouseMiddleClick;
	} MouseClick;

	typedef std::function<void(int, int, int)> KeyEventCallbackFunc;
	typedef std::function<void(unsigned int)> CharEventCallbackFunc;

	void SetCursorShape(CursorShape shape);
	CursorShape GetCursorShape();

	bool CheckInputEnabled(int x, int y);
	void GetMousePosition(int& x, int& y);
	bool IsMousePositionOnScreen(int x, int y);
	void GetMouseButton(bool& left, bool& right, bool& middle);
	MouseClick GetMouseClick();
	std::shared_ptr<Container> GetMouseOverContainer();
	bool IsMouseOverThisContainer();

	void AddKeyEventCallback(KeyEventCallbackFunc func);
	void AddCharEventCallback(CharEventCallbackFunc func);

	void KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CharEventCallback(GLFWwindow* window, unsigned int codepoint);
    void ProcessInput();
}