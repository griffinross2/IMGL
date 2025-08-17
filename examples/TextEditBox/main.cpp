#include "Application.h"

#include "Interactable.h"
#include "Container.h"
#include "Primitives.h"
#include "Text.h"
#include "Input.h"
#include "Style.h"
#include "TextEditBox.h"

using namespace IMGL;

void keyEventCallback(int key, int action, int mod) {
	textEditBoxKeyEventCallback(key, action, mod);
}

void charEventCallback(unsigned int codepoint) {
    textEditBoxCharEventCallback(codepoint);
}

int main() {
    Application app;
    Application::setWindowTitle("Basic Window Example");
    Application::setWindowSize(800, 600);

    double lastTime = glfwGetTime();
    int frameCount = 0;
    
	TextEditBox textEditBox("Test string", 300, 280, 200, 40);

    // Main loop
    while (!Application::shouldClose()) {

        // Register key callbacks
        AddKeyEventCallback(keyEventCallback);
		AddCharEventCallback(charEventCallback);

        // Draw text edit box
		textEditBox.draw();

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

void drawTextEditBox() {
	int x = 300;
	int y = 280;
	int width = 200;
	int height = 40;
    int textSize = 20;

    
}
