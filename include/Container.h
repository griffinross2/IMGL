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
    void ContainerBackground(const Color& color);
    void ContainerBegin(int x, int y, int width, int height);
    void ContainerEnd();

}