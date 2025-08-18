#include "Application.h"

#include "Interactable.h"
#include "Container.h"
#include "Primitives.h"
#include "Text.h"
#include "Input.h"
#include "Style.h"
#include "DraggableResizableContainer.h"

using namespace IMGL;

int main() {
    Application app;
    Application::setWindowTitle("Basic Window Example");
    Application::setWindowSize(800, 600);

    double lastTime = glfwGetTime();
    int frameCount = 0;

    DraggableResizableContainer draggable("Draggable Resizable Container", 100, 150, 500, 300);

    // Main loop
    while (!Application::shouldClose()) {

        // Draw draggable container
        draggable.DrawBegin();

        TextSize(24);
        TextColor({ 1.0f, 0.0f, 1.0f, 1.0f });
        DrawText("Hello, Draggable Resizable Container!", 10, draggable.GetHeight()/2 - 10);
        TextSize(DefaultTextSize);
        TextColor(DefaultTextColor);

        draggable.DrawEnd();


        Application::draw();

        frameCount++;
        if (glfwGetTime() - lastTime >= 1.0) {
            Application::setWindowTitle(("FPS: " + std::to_string(frameCount)).c_str());
            frameCount = 0;
            lastTime = glfwGetTime();
        }
    }

    return 0;
}