#include "DraggableResizableContainer.h"

#include "Container.h"
#include "Input.h"
#include "Primitives.h"
#include "Style.h"
#include "Text.h"
#include "Application.h"

#include <iostream>

using namespace IMGL;

DraggableResizableContainer::DraggableResizableContainer(const std::string& title, int x, int y, unsigned int width, unsigned int height, unsigned int minWidth, unsigned int minHeight) {
    m_title = title;
    m_dragging = false;
    m_resizing = false;
    m_dragOffsetX = 0;
    m_dragOffsetY = 0;
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_minWidth = minWidth;
    m_minHeight = minHeight;
}

DraggableResizableContainer::~DraggableResizableContainer() {
}

// Reimplement the begin, end structure from normal containers
void DraggableResizableContainer::drawBegin() {
    // Get some dimensions first
    float xscale = Application::hscale();
    float yscale = Application::vscale();
    unsigned int textWidth, textHeight;
    TextSize(DefaultTextSize * (xscale + yscale) / 2);
    GetTextDimensions(m_title, textWidth, textHeight);
    int titleBarHeight = textHeight + 15;

    unsigned int width, height;
    GetCurrentSpace(width, height);

    // Begin the container
    ContainerBegin(m_title);
    ContainerMove(m_x, m_y);
    ContainerSize(m_width, m_height);
    ContainerDraw();

    // Draw title bar
    DrawRectangle(0, m_height - titleBarHeight, m_width, titleBarHeight, { 0.15f, 0.15f, 0.15f, 1.0f });
    DrawBorder(0, m_height - titleBarHeight, m_width, titleBarHeight, GetContainerBorderColor(), GetContainerBorderThickness());
    DrawText(m_title, 5, m_height - (titleBarHeight + textHeight) / 2);

    // Resize arrow
    DrawTriangle(m_width - 5 - 5*xscale, 5, 
                 m_width - 5, 5, 
                 m_width - 5, 5 + 5*yscale,
                 GetContainerBorderColor());

    // Check input
    int mx, my;
    bool leftButton, rightButton, middleButton;
    GetMousePosition(mx, my);
    GetMouseButton(leftButton, rightButton, middleButton);

    if (CheckRectangleBounds(0, m_height - titleBarHeight, m_width, titleBarHeight, mx, my) && CheckInputEnabled(mx, my)) {
        // Drag cursor shape for the title bar
        SetCursorShape(CURSOR_RESIZE_ALL);
    }
    if (CheckRectangleBounds(m_width - 5 - 5*xscale, 0, 5 + 5*xscale, 5+5*yscale, mx, my) && CheckInputEnabled(mx, my)) {
        // Resize NWSE cursor shape for the resize triangle
        SetCursorShape(CURSOR_NWSE_RESIZE);
    }

    // Check if the title bar is being dragged
    std::cout << GetMouseOverContainer() << std::endl;
	//std::cout << mx << ", " << my << std::endl;
    if (!m_dragging && !m_resizing && leftButton && IsMouseOverThisContainer() && CheckRectangleBounds(0, m_height - titleBarHeight, m_width, titleBarHeight, mx, my) && CheckInputEnabled(mx, my)) {
        m_dragging = true;
        m_dragOffsetX = mx - m_x;
        m_dragOffsetY = my - m_y;
    } else if (m_dragging && leftButton) {
        m_x = mx - m_dragOffsetX;
        m_y = my - m_dragOffsetY;
    } else {
        m_dragging = false;
    }

    // Bound drag
    if (m_x < 0) m_x = 0;
    if (m_x + m_width > static_cast<int>(width)) {
        m_x = width - m_width;
    }
    if (m_y < 0) m_y = 0;
    if (m_y + m_height > static_cast<int>(height)) {
        m_y = height - m_height;
    }

    // Check if the resize triangle is being dragged
    if (!m_dragging && !m_resizing && leftButton && CheckRectangleBounds(m_width - 5 - 5 * xscale, 0, 5 + 5 * xscale, 5 + 5 * yscale, mx, my) && CheckInputEnabled(mx, my)) {
        m_resizing = true;
        m_dragOffsetY = my - m_y;
    } else if (m_resizing && leftButton) {
        m_width = mx - m_x;
        if (m_width < std::max(m_minWidth, static_cast<int>(textWidth) + 10)) {
            m_width = std::max(m_minWidth, static_cast<int>(textWidth) + 10);
        }
        m_height = m_y + m_height - my;
        m_y = my;
        if (m_height < m_minHeight + titleBarHeight) {
            m_y = my + m_height - m_minHeight - titleBarHeight;
            m_height = m_minHeight + titleBarHeight;
        }
    } else {
        m_resizing = false;
    }

    // Bound resize
    if (m_x + m_width > static_cast<int>(width)) {
        m_width = width - m_x;
    }
    if (m_y < 0) {
        m_height = m_y + m_height;
        m_y = 0;
    }
    if (m_y + m_height > static_cast<int>(height)) {
        m_height = height - m_y;
    }
}

void DraggableResizableContainer::drawEnd() {
    ContainerEnd();
}

bool DraggableResizableContainer::pressed() {
    int mx, my;
    bool leftButton, rightButton, middleButton;
    GetMousePosition(mx, my);
    GetMouseButton(leftButton, rightButton, middleButton);
    return leftButton && CheckRectangleBounds(m_x, m_y, m_width, m_height, mx, my);
}