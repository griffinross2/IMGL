#include "Container.h"

#include "Render.h"
#include "Primitives.h"
#include "Application.h"

#include <glad/gl.h>
#include <glm/glm.hpp>


static IMGL::Color s_container_color = IMGL::DefaultContainerColor;
static IMGL::Color s_container_border_color = IMGL::DefaultContainerBorderColor;
unsigned int s_container_border_thickness = IMGL::DefaultContainerBorderThickness;

void IMGL::ToScreenSpace(int& x, int& y) {
    // Convert the coordinates from their position within the container to screen pixels
    if (!IMGL::containerStack.empty()) {
        const IMGL::Container& container = IMGL::containerStack.back();
        x += container.x;
        y += container.y;
    }
}

void IMGL::ContainerBackground(const Color& color) {
    s_container_color = color;
}

void IMGL::ContainerBorderColor(const Color& color) {
    s_container_border_color = color;
}

void IMGL::ContainerBorderThickness(unsigned int thickness) {
    s_container_border_thickness = thickness;
}

void IMGL::ContainerBegin(int x, int y, int width, int height) {
    // Clip the container to the previous container's dimensions
    if (!containerStack.empty()) {
        const Container& container = containerStack.back();
        width = std::min(width, container.width - x);
        height = std::min(height, container.height - y);
    }

    // Set the scissor area to the container's dimensions
    int scissorX = x;
    int scissorY = y;
    ToScreenSpace(scissorX, scissorY);
    IMGL::Renderer::get()->renderList.commands.push_back(IMGL::ScissorCommand{static_cast<unsigned int>(scissorX), static_cast<unsigned int>(scissorY), static_cast<unsigned int>(width), static_cast<unsigned int>(height)});

    // Draw the container background
    IMGL::DrawRectangle(x, y, width, height, s_container_color);

	// Draw the container border
    if (s_container_border_thickness > 0) {
        IMGL::DrawBorder(x, y, width, height, s_container_border_color, s_container_border_thickness);
    }

    // Push the container onto the stack
    ToScreenSpace(x, y);
    Container newContainer = { width, height, x, y };
    containerStack.push_back(newContainer);
}

void IMGL::ContainerEnd() {
    if (!containerStack.empty()) {
        containerStack.pop_back();
    }

    // Restore the scissor to the previous container's dimensions
    if (!containerStack.empty()) {
        const Container& container = containerStack.back();
        IMGL::Renderer::get()->renderList.commands.push_back(IMGL::ScissorCommand{static_cast<unsigned int>(container.x), static_cast<unsigned int>(container.y), static_cast<unsigned int>(container.width), static_cast<unsigned int>(container.height)});
    } else {
        // If no containers are left, expand the scissor to the full window size
        IMGL::Renderer::get()->renderList.commands.push_back(IMGL::ScissorCommand{0, 0, IMGL::Application::width(), IMGL::Application::height()});
    }

    // Restore default attributes
    s_container_color = IMGL::DefaultContainerColor;
	s_container_border_color = IMGL::DefaultContainerBorderColor;
	s_container_border_thickness = IMGL::DefaultContainerBorderThickness;
}