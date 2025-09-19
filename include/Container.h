#pragma once

#include "Application.h"
#include "Style.h"
#include "Render.h"

#include <vector>
#include <map>
#include <list>
#include <string>
#include <memory>

// Container.h
// A container is a UI element that contains other elements within it.
// Essentially, the container just redefines the coordinate space for anything drawn within it.

namespace IMGL {

    class Container {

    public:
        Container() : width(0), height(0), x(0), y(0), canFocus(false) {}
		Container(int width, int height, int x, int y) : width(width), height(height), x(x), y(y), canFocus(true) {}
		~Container() = default;

        bool canFocus;
        int width;
        int height;
        int x;
        int y;
		RenderList renderList;
    };

	// Persistent storage for containers
	static std::map<std::string, std::shared_ptr<Container>> containers;

	// Persistent stack to track the order of containers on top of each other
	// Any container that is focused will be moved to the top of this stack
    static std::list<std::shared_ptr<Container>> focusStack;

	// Per frame stack that tracks the nested containers we are drawing inside of
    static std::vector<std::shared_ptr<Container>> containerStack;

    // Root container
	static const std::shared_ptr<Container> rootContainer = std::make_shared<Container>();

    void ToScreenSpace(int& x, int& y);
    void GetCurrentSpace(unsigned int& width, unsigned int& height);

    void ContainerBackground(const Color& color);
	void ContainerBorderColor(const Color& color);
	void ContainerBorderThickness(unsigned int thickness);
    Color GetContainerBackground();
    Color GetContainerBorderColor();
    unsigned int GetContainerBorderThickness();

    void ContainerBegin(const std::string& name);
	void ContainerMove(int x, int y);
	void ContainerSize(int width, int height);
	void ContainerFocus();
    void ContainerEnd();

}