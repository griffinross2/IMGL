#include "Input.h"

#include <iostream>
#include <array>
#include <vector>

namespace IMGL {

    static std::array<bool, 3> s_mouseButtonStates = { false, false, false }; // Left, Right, Middle
    static std::array<std::pair<int, int>, 3> s_mousePressedAt = { std::pair{-1, -1}, std::pair{-1, -1}, std::pair{-1, -1} };
    static std::array<std::pair<int, int>, 3> s_mouseReleasedAt = { std::pair{-1, -1}, std::pair{-1, -1}, std::pair{-1, -1} };

    void ProcessInput(GLFWwindow* window) {
        // A click happens on an element when the mouse button is pressed on that element, then 
        // released while still over that element.
        for (int button = GLFW_MOUSE_BUTTON_LEFT; button <= GLFW_MOUSE_BUTTON_MIDDLE; button++) {
            bool clicked = false;

            if (glfwGetMouseButton(window, button) == GLFW_PRESS) {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);

                // If the button was not already pressed, register the press
                if (!s_mouseButtonStates[button]) {
                    s_mousePressedAt[button] = { (int)xpos, (int)ypos };
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
                    s_mouseReleasedAt[button] = { (int)xpos, (int)ypos };
                }

                // Record the state
                s_mouseButtonStates[button] = false;
            }

            // If the mouse was clicked, check if it was within any registered input boxes
            if (clicked) {
                std::cout << "Mouse Button " << button << " clicked at: " 
                          << s_mouseReleasedAt[button].first << ", " 
                          << s_mouseReleasedAt[button].second << std::endl;
            }
        }
    }

}