#include "Application.h"

#include "Interactable.h"
#include "Container.h"
#include "Primitives.h"
#include "Text.h"
#include "Input.h"
#include "Style.h"

using namespace IMGL;

int currentTab = 0;
void drawTabBar();
void drawTabZero();
void drawTabOne();
void drawTabTwo();

int main() {
    Application app;
    Application::setWindowTitle("Basic Window Example");
    Application::setWindowSize(800, 600);

    double lastTime = glfwGetTime();
    int frameCount = 0;
    

    // Main loop
    while (!Application::shouldClose()) {
		// Draw tab bar
		drawTabBar();

        // Draw current tab
        switch(currentTab) {
            case 0:
                drawTabZero();
                break;
            case 1:
                drawTabOne();
                break;
            case 2:
                drawTabTwo();
                break;
            default:
                drawTabZero();
                break;
		}

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

void drawTabBar() {
    unsigned int height = Application::height();
	unsigned int width = Application::width();

	DrawRectangle(0, height - 20, width, 1, DefaultButtonBorderColor);

    bool hovered, pressed, clicked;
	ButtonColor(currentTab == 0 ? Color{ 0.2f, 0.2f, 0.2f, 1.0f } : DefaultButtonColor);
    DrawButton("Tab 1", 0, height - 20, 75, 20, hovered, pressed, clicked);
    if (clicked) {
        currentTab = 0;
    }

    ButtonColor(currentTab == 1 ? Color{ 0.2f, 0.2f, 0.2f, 1.0f } : DefaultButtonColor);
    DrawButton("Tab 2", 75, height - 20, 75, 20, hovered, pressed, clicked);
    if (clicked) {
        currentTab = 1;
    }

    ButtonColor(currentTab == 2 ? Color{ 0.2f, 0.2f, 0.2f, 1.0f } : DefaultButtonColor);
    DrawButton("Tab 3", 150, height - 20, 75, 20, hovered, pressed, clicked);
    if (clicked) {
        currentTab = 2;
    }
}

void drawTabZero() {
    unsigned int height = Application::height();
    unsigned int width = Application::width();

    ContainerBorderThickness(0);
	ContainerBackground({ 0.6f, 0.3f, 0.3f, 0.5f });
	ContainerBegin(0, 0, width, height-20);
    ContainerBackground(DefaultContainerColor);

    
	// Draw some text
	TextSize(24);
	TextColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	DrawText("You are on Tab 1!", 10, height/2);
	TextSize(DefaultTextSize);
	TextColor(DefaultTextColor);

    ContainerEnd();
}

void drawTabOne() {
    unsigned int height = Application::height();
    unsigned int width = Application::width();

    ContainerBorderThickness(0);
    ContainerBackground({ 0.3f, 0.6f, 0.3f, 0.5f });
    ContainerBegin(0, 0, width, height - 20);
    ContainerBackground(DefaultContainerColor);
    
    // Draw some text
    TextSize(24);
    TextColor({ 0.0f, 1.0f, 1.0f, 1.0f });
    DrawText("You are on Tab 2!", 10, height/2);
    TextSize(DefaultTextSize);
    TextColor(DefaultTextColor);

    ContainerEnd();
}

void drawTabTwo() {
    unsigned int height = Application::height();
    unsigned int width = Application::width();
    
    ContainerBorderThickness(0);
    ContainerBackground({ 0.3f, 0.3f, 0.6f, 0.5f });
    ContainerBegin(0, 0, width, height - 20);
    ContainerBackground(DefaultContainerColor);
    
    // Draw some text
    TextSize(24);
    TextColor({ 1.0f, 1.0f, 0.0f, 1.0f });
    DrawText("You are on Tab 3!", 10, height/2);
    TextSize(DefaultTextSize);
    TextColor(DefaultTextColor);

    ContainerEnd();
}