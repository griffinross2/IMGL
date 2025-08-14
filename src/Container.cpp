#include "Container.h"

#include <stack>

struct Container {
    unsigned int width;
    unsigned int height;
    unsigned int x;
    unsigned int y;
};

static std::stack<Container> containerStack;

void IMGL::ContainerBegin(unsigned int width, unsigned int height, unsigned int x, unsigned int y) {
    Container newContainer = { width, height, x, y };
    containerStack.push(newContainer);
}

void IMGL::ContainerEnd() {
    if (!containerStack.empty()) {
        containerStack.pop();
    }
}