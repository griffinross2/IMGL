#include "Application.h"

#include "Container.h"
#include "Primitives.h"
#include "Text.h"

int main() {
    IMGL::Application app;
    IMGL::Application::setWindowTitle("Basic Window Example");
    IMGL::Application::setWindowSize(800, 600);

    double lastTime = glfwGetTime();
    int frameCount = 0;
    

    // Check if main window is open
    while (!IMGL::Application::shouldClose()) {

        IMGL::ContainerBegin(100, 100, 600, 300);

        IMGL::ContainerBackground({ 0.5f, 0.2f, 0.2f, 1.0f });
        IMGL::ContainerBegin(100, 100, 400, 100);

        IMGL::DrawRectangle(10, 10, 50, 50, { 0.2f, 0.5f, 0.2f, 1.0f });
		IMGL::TextColor({ 1.0f, 0.0f, 1.0f, 1.0f });
        IMGL::DrawText("Hello, IMGL!", 70, 20);

        IMGL::ContainerEnd();
        
        IMGL::ContainerEnd();

        IMGL::Application::draw();

        frameCount++;
        if (glfwGetTime() - lastTime >= 1.0) {
            IMGL::Application::setWindowTitle(("FPS: " + std::to_string(frameCount)).c_str());
            frameCount = 0;
            lastTime = glfwGetTime();
        }
    }

    return 0;
}