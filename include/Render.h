#pragma once

#include "Shader.h"

#include <vector>
#include <variant>

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
        void (*callback)();
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
        static void Render();
        static void Destroy();

        static unsigned int VAO, VBO, EBO;
        static Shader shader;
        static RenderList renderList;

    };

}