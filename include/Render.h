#pragma once

#include <vector>
#include <variant>
#include <memory>

// Render.h
// This file contains the rendering functions for the IMGL library.

namespace IMGL {

    // A single draw call
    struct DrawCommand {
        unsigned int idxOff;
        unsigned int idxCount;
    };

    // A custom callback
    struct CustomCallback {
        void (*callback)(void*);
        void* data;
    };

    // A scissor call
    struct ScissorCommand {
        unsigned int x, y, width, height;
    };

    typedef std::variant<
        DrawCommand,
        CustomCallback,
        ScissorCommand
    > RenderCommand;

    struct RenderList {
        std::vector<RenderCommand> commands;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    class Renderer {

    public:
        Renderer();
        ~Renderer() = default;

        static Renderer* get();
        static RenderList* RenderList();
        static void Render();
        static void Destroy();

        static unsigned int VAO, VBO, EBO;

    private:
        static void RenderContainer(std::shared_ptr<void> container);

    };

}