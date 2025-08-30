#include "Application.h"

#include "Interactable.h"
#include "Container.h"
#include "Primitives.h"
#include "Text.h"
#include "Input.h"
#include "Style.h"
#include "DraggableResizableContainer.h"

using namespace IMGL;

DraggableResizableContainer draggable("Draggable Resizable Container", 100, 150, 500, 300);
DraggableResizableContainer draggable2("Draggable Resizable Container 2", 150, 100, 500, 300);

void drawFirstContainer();
void drawSecondContainer();
int focus = 0;

int main() {
    Application app;
    Application::setWindowTitle("Basic Window Example");
    Application::setWindowSize(800, 600);

    double lastTime = glfwGetTime();
    int frameCount = 0;

    // Main loop
    while (!Application::shouldClose()) {
        // Draw bottom (unfocused) container
        SetInputOff();
        if (!focus) drawFirstContainer(); else drawSecondContainer();
        
        // Draw top (focused) container
        SetInputOn();
        if (!focus) {
            SetInputMask(draggable2.getX(), draggable2.getY(), draggable2.getWidth(), draggable2.getHeight());
            drawSecondContainer();
        }
        else {
            SetInputMask(draggable.getX(), draggable.getY(), draggable.getWidth(), draggable.getHeight());
            drawFirstContainer();
        }
        InputDemask();

        // Set new focus
        if (!focus && draggable.pressed() && !draggable2.pressed()) focus = 1;
        else if (focus && draggable2.pressed() && !draggable.pressed()) focus = 0;

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

void drawFirstContainer() {
    draggable.drawBegin();

    TextSize(24);
    TextColor({ 1.0f, 0.0f, 1.0f, 1.0f });
    DrawText("Hello, Draggable Resizable Container!", 10, draggable.getHeight() / 2 - 10);
    TextSize(DefaultTextSize);
    TextColor(DefaultTextColor);

    draggable.drawEnd();
}

void drawSecondContainer() {
    draggable2.drawBegin();

    TextSize(24);
    TextColor({ 0.0f, 1.0f, 1.0f, 1.0f });
    DrawText("Hello, Draggable Resizable Container 2!", 10, draggable2.getHeight() / 2 - 10);
    TextSize(DefaultTextSize);
    TextColor(DefaultTextColor);

    draggable2.drawEnd();
}