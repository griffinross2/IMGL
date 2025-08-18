#pragma once

#include "Style.h"

#include <vector>

// Container.h
// A container is a UI element that contains other elements within it.
// Essentially, the container just redefines the coordinate space for anything drawn within it.

namespace IMGL {

    struct Container {
        int width;
        int height;
        int x;
        int y;
    };

    static std::vector<Container> containerStack;

    void ToScreenSpace(int& x, int& y);
    void GetCurrentSpace(unsigned int& width, unsigned int& height);

    void ContainerBackground(const Color& color);
	void ContainerBorderColor(const Color& color);
	void ContainerBorderThickness(unsigned int thickness);
    Color GetContainerBackground();
    Color GetContainerBorderColor();
    unsigned int GetContainerBorderThickness();

    void ContainerBegin(int x, int y, int width, int height);
    void ContainerEnd();

}