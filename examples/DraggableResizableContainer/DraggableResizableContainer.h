#pragma once

#include <string>

class DraggableResizableContainer {

public:
    DraggableResizableContainer(const std::string& title, int x, int y, unsigned int width, unsigned int height, unsigned int minWidth = 20, unsigned int minHeight = 20);
    ~DraggableResizableContainer();

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

    // Reimplement the begin, end structure from normal containers
    void DrawBegin();
    void DrawEnd();

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