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

    void ToScreenSpace(int& x, int& y);
    void GetCurrentSpace(unsigned int& width, unsigned int& height);

    void ContainerBackground(const Color& color);
	void ContainerBorderColor(const Color& color);
	void ContainerBorderThickness(unsigned int thickness);
    Color GetContainerBackground();
    Color GetContainerBorderColor();
    unsigned int GetContainerBorderThickness();

    const std::map<std::string, std::shared_ptr<Container>>& GetContainers();
	const std::list<std::shared_ptr<Container>>& GetFocusStack();
    const std::vector<std::shared_ptr<Container>>& GetContainerStack();
	const std::shared_ptr<Container>& GetRootContainer();

    void ContainerBegin(const std::string& name);
	void ContainerMove(int x, int y);
	void ContainerSize(int width, int height);
	void ContainerFocus();
	void ContainerFocus(std::shared_ptr<Container> container);
    void ContainerEnd();

}