#pragma once

#include <string>

class DraggableResizableContainer {

public:
    DraggableResizableContainer(const std::string& title, int x, int y, unsigned int width, unsigned int height, unsigned int minWidth = 20, unsigned int minHeight = 20);
    ~DraggableResizableContainer();

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    // We can see if the container has been pressed, for assigning focus
    bool pressed();

    // Reimplement the begin, end structure from normal containers
    void drawBegin();
    void drawEnd();

private:
    std::string m_title;
    bool m_dragging;
    bool m_resizing;
    int m_dragOffsetX;
    int m_dragOffsetY;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_minWidth;
    int m_minHeight;
};