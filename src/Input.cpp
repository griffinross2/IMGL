#include "Input.h"

#include "Container.h"
#include "Application.h"

#include <iostream>
#include <array>
#include <vector>

namespace IMGL {

    static std::array<bool, 3> s_mouseButtonStates = { false, false, false }; // Left, Right, Middle
    static std::array<std::pair<int, int>, 3> s_mousePressedAt = { std::pair{-1, -1}, std::pair{-1, -1}, std::pair{-1, -1} };
    static std::array<std::pair<int, int>, 3> s_mouseReleasedAt = { std::pair{-1, -1}, std::pair{-1, -1}, std::pair{-1, -1} };

	static bool s_mouseLeftClick = false;
	static bool s_mouseRightClick = false;
	static bool s_mouseMiddleClick = false;

	static std::vector<void(*)(int key, int action, int mod)> s_keyCallbacks;
	static std::vector<void(*)(unsigned int codepoint)> s_charCallbacks;

    void GetMousePosition(int& x, int& y) {
        double xpos, ypos;
        glfwGetCursorPos(Application::getWindow(), &xpos, &ypos);
		x = static_cast<int>(xpos);
		y = static_cast<int>(Application::height() - ypos);
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

        for (int button = GLFW_MOUSE_BUTTON_LEFT; button <= GLFW_MOUSE_BUTTON_MIDDLE; button++) {
            bool clicked = false;

            if (glfwGetMouseButton(window, button) == GLFW_PRESS) {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);

                // If the button was not already pressed, register the press
                if (!s_mouseButtonStates[button]) {
                    s_mousePressedAt[button] = { (int)xpos, height - (int)ypos };
                }

                // Record the state
                s_mouseButtonStates[button] = true;
            }
            else if (glfwGetMouseButton(window, button) == GLFW_RELEASE && s_mouseButtonStates[button]) {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);

                // If the button was not already released, register the release
                if (s_mouseButtonStates[button]) {
                    clicked = true;
                    s_mouseReleasedAt[button] = { (int)xpos, height - (int)ypos };
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