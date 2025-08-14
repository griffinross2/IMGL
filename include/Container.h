
#pragma once

// Container.h
// A container is a UI element that contains other elements within it.
// Essentially, the container just redefines the coordinate space for anything drawn within it.

namespace OpenGLGui {

    void ContainerBegin(unsigned int width, unsigned int height, unsigned int x = 0, unsigned int y = 0);
    void ContainerEnd();

}