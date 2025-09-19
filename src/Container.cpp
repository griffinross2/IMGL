#include "Container.h"

#include "Render.h"
#include "Primitives.h"
#include "Application.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace IMGL {

static Color s_container_color = DefaultContainerColor;
static Color s_container_border_color = DefaultContainerBorderColor;
unsigned int s_container_border_thickness = DefaultContainerBorderThickness;

static void FocusContainer(std::shared_ptr<Container> container) {
    focusStack.remove(container);
    focusStack.push_back(container);
}

static std::shared_ptr<Container> FindOrCreateContainer(const std::string& name, int x, int y, int width, int height) {
    if (containers.find(name) == containers.end()) {
		// Container does not already exist, create it
		std::shared_ptr<Container> newContainer = std::make_shared<Container>(width, height, x, y);
        containers[name] = newContainer;
        FocusContainer(newContainer);
        return newContainer;
    }
    else {
		return containers[name];
    }
}

void ToScreenSpace(int& x, int& y) {
    // Convert the coordinates from their position within the container to screen pixels
    for (int i = static_cast<int>(containerStack.size()) - 1; i >= 0; --i) {
        std::shared_ptr<Container> container = containerStack[i];
        x += container->x;
        y += container->y;
	}
}

void GetCurrentSpace(unsigned int& width, unsigned int& height) {
    if (!containerStack.empty()) {
        std::shared_ptr<Container> container = containerStack.back();
        width = container->width;
        height = container->height;
    } else {
        width = Application::width();
        height = Application::height();
    }
}

void ContainerBackground(const Color& color) {
    s_container_color = color;
}

void ContainerBorderColor(const Color& color) {
    s_container_border_color = color;
}

void ContainerBorderThickness(unsigned int thickness) {
    s_container_border_thickness = thickness;
}

Color GetContainerBackground() {
    return s_container_color;
}

Color GetContainerBorderColor() {
    return s_container_border_color;
}

unsigned int GetContainerBorderThickness() {
    return s_container_border_thickness;
}

void ContainerBegin(const std::string& name) {
	int x = 50;
	int y = 50;
    int width = 100;
	int height = 100;

    // Clip the container to the previous container's dimensions
    if (!containerStack.empty()) {
        std::shared_ptr<Container> container = containerStack.back();
        width = std::min(width, container->width - x);
        height = std::min(height, container->height - y);
    }

    // Get or create the container
    std::shared_ptr<Container> container = FindOrCreateContainer(name, x, y, width, height);
	x = container->x;
	y = container->y;
	width = container->width;
	height = container->height;

    // Set the scissor area to the container's dimensions
    int scissorX = x;
    int scissorY = y;
    ToScreenSpace(scissorX, scissorY);
    Renderer::RenderList()->commands.push_back(ScissorCommand{static_cast<unsigned int>(scissorX), static_cast<unsigned int>(scissorY), static_cast<unsigned int>(width), static_cast<unsigned int>(height)});

    // Draw the container background
    DrawRectangle(x, y, width, height, s_container_color);

	// Draw the container border
    if (s_container_border_thickness > 0) {
        DrawBorder(x, y, width, height, s_container_border_color, s_container_border_thickness);
    }

    // Push the container onto the stack
    containerStack.push_back(container);
}

void ContainerEnd() {
    if (!containerStack.empty()) {
        containerStack.pop_back();
    }

    // Restore the scissor to the previous container's dimensions
    if (!containerStack.empty()) {
        std::shared_ptr<Container> container = containerStack.back();
		int scissorX = container->x;
		int scissorY = container->y;
		ToScreenSpace(scissorX, scissorY);
        Renderer::RenderList()->commands.push_back(ScissorCommand{static_cast<unsigned int>(scissorX), static_cast<unsigned int>(scissorY), static_cast<unsigned int>(container->width), static_cast<unsigned int>(container->height)});
    } else {
        // If no containers are left, expand the scissor to the full window size
        Renderer::RenderList()->commands.push_back(ScissorCommand{0, 0, Application::width(), Application::height()});
    }
}

void ContainerMove(int x, int y) {
    if (!containerStack.empty()) {
        std::shared_ptr<Container> container = containerStack.back();
        container->x = x;
        container->y = y;
    }
}

void ContainerSize(int width, int height) {
    if (!containerStack.empty()) {
        std::shared_ptr<Container> container = containerStack.back();
        container->width = width;
        container->height = height;
    }
}

void ContainerFocus() {
    if (!containerStack.empty()) {
        std::shared_ptr<Container> container = containerStack.back();
		if (container->canFocus) {
            FocusContainer(container);
        }
    }
}

}