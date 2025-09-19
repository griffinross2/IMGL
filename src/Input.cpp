#include "Input.h"

#include "Container.h"
#include "Application.h"
#include "Primitives.h"

#include <iostream>
#include <array>
#include <vector>

namespace IMGL {

	static int s_mouseX = 0, s_mouseY = 0;
    static std::array<bool, 3> s_mouseButtonStates = { false, false, false }; // Left, Right, Middle
    static std::array<std::pair<int, int>, 3> s_mousePressedAt = { std::pair{-1, -1}, std::pair{-1, -1}, std::pair{-1, -1} };
    static std::array<std::pair<int, int>, 3> s_mouseReleasedAt = { std::pair{-1, -1}, std::pair{-1, -1}, std::pair{-1, -1} };

	static bool s_mouseLeftClick = false;
	static bool s_mouseRightClick = false;
	static bool s_mouseMiddleClick = false;

	static std::vector<void(*)(int key, int action, int mod)> s_keyCallbacks;
	static std::vector<void(*)(unsigned int codepoint)> s_charCallbacks;

    static CursorShape s_currentCursorShape = CURSOR_ARROW;

    static bool s_inputEnabled = true;
    static bool s_inputMaskEnabled = false;
    static int s_inputMaskX = 0;
    static int s_inputMaskY = 0;
    static int s_inputMaskW = 0;
    static int s_inputMaskH = 0;

    bool CheckInputEnabled(int x, int y) {
        // Check if inputs are completely disabled
        if (!s_inputEnabled) {
            return false;
        }

        // Check input mask
        if (s_inputMaskEnabled && !CheckRectangleBounds(s_inputMaskX, s_inputMaskY, s_inputMaskW, s_inputMaskH, x, y)) {
            return false;
        }

        return true;
    }

    void SetInputOn() {
        s_inputEnabled = true;
    }

    void SetInputOff() {
        s_inputEnabled = false;
    }

    void SetInputMask(int x, int y, int w, int h) {
        ToScreenSpace(x, y);
        s_inputMaskX = x;
        s_inputMaskY = y;
        s_inputMaskW = w;
        s_inputMaskH = h;
        s_inputMaskEnabled = true;
    }

    void InputDemask() {
        s_inputMaskEnabled = false;
    }

    void SetCursorShape(CursorShape shape) {
        s_currentCursorShape = shape;
    }

    CursorShape GetCursorShape() {
        return s_currentCursorShape;
    }

    void GetMousePosition(int& x, int& y) {
		x = s_mouseX;
		y = s_mouseY;
    }

    bool IsMousePositionOnScreen() {
        return s_mouseX >= 0 && s_mouseX < static_cast<int>(Application::width()) && s_mouseY >= 0 && s_mouseY < static_cast<int>(Application::height());
    }

    std::shared_ptr<Container> GetMouseOverContainer() {
        for (auto it = GetFocusStack().rbegin(); it != GetFocusStack().rend(); ++it) {
            std::shared_ptr<Container> container = *it;
			if (CheckRectangleBounds(container->x, container->y, container->width, container->height, s_mouseX, s_mouseY)) {
                return container;
            }
        }
		return GetRootContainer();
    }

    bool IsMouseOverThisContainer() {
        if (!GetContainerStack().empty()) {
			return GetContainerStack().back() == GetMouseOverContainer();
        }
        return false;
	}

    MouseClick GetMouseClick() {
		int x, y;
		GetMousePosition(x, y);
        MouseClick click = {
			.x = x,
			.y = y,
			.mouseLeftClick = s_mouseLeftClick,
			.mouseRightClick = s_mouseRightClick,
			.mouseMiddleClick = s_mouseMiddleClick,
        };

		return click;
	}

    void GetMouseButton(bool& left, bool& right, bool& middle) {
        left = s_mouseButtonStates[GLFW_MOUSE_BUTTON_LEFT];
        right = s_mouseButtonStates[GLFW_MOUSE_BUTTON_RIGHT];
        middle = s_mouseButtonStates[GLFW_MOUSE_BUTTON_MIDDLE];
    }

    void AddKeyEventCallback(void func(int key, int action, int mod)) {
		s_keyCallbacks.push_back(func);
    }

    void AddCharEventCallback(void func(unsigned int codepoint)) {
        s_charCallbacks.push_back(func);
    }

    void KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        for (const auto& cb : s_keyCallbacks) {
			cb(key, action, mods);
		}
	}

    void CharEventCallback(GLFWwindow* window, unsigned int codepoint) {
        for (const auto& cb : s_charCallbacks) {
            cb(codepoint);
        }
	}

    void ProcessInput() {
        // A click happens on an element when the mouse button is pressed on that element, then 
        // released while still over that element.
        s_keyCallbacks.clear();
		s_charCallbacks.clear();

		int height = Application::height();
		GLFWwindow* window = Application::getWindow();

		// Record mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		s_mouseX = static_cast<int>(xpos);
		s_mouseY = height - static_cast<int>(ypos);

        for (int button = GLFW_MOUSE_BUTTON_LEFT; button <= GLFW_MOUSE_BUTTON_MIDDLE; button++) {
            bool clicked = false;

            if (glfwGetMouseButton(window, button) == GLFW_PRESS) {
                // If the button was not already pressed, register the press
                // Also, when a container is pressed, focus it
                if (!s_mouseButtonStates[button]) {
                    s_mousePressedAt[button] = { s_mouseX, s_mouseY };
                    ContainerFocus(GetMouseOverContainer());
                }

                // Record the state
                s_mouseButtonStates[button] = true;
            }
            else if (glfwGetMouseButton(window, button) == GLFW_RELEASE && s_mouseButtonStates[button]) {
                // If the button was not already released, register the release
                if (s_mouseButtonStates[button]) {
                    clicked = true;
                    s_mouseReleasedAt[button] = { s_mouseX, s_mouseY };
                }

                // Record the state
                s_mouseButtonStates[button] = false;
            }

            // Record clicks
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                s_mouseLeftClick = clicked;
            }
            if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                s_mouseRightClick = clicked;
			}
            if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                s_mouseMiddleClick = clicked;
            }
        }
    }

}