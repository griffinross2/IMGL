#include "Container.h"

#include <stack>

struct Container {
    unsigned int width;
    unsigned int height;
    unsigned int x;
    unsigned int y;
};

static std::stack<Container> containerStack;

void OpenGLGui::ContainerBegin(unsigned int width, unsigned int height, unsigned int x, unsigned int y) {
    Container newContainer = { width, height, x, y };
    containerStack.push(newContainer);
}

void OpenGLGui::ContainerEnd() {
    if (!containerStack.empty()) {
        containerStack.pop();
    }
}