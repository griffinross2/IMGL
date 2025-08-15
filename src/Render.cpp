#include "Render.h"

#include "Container.h"
#include "Application.h"
#include "Shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace IMGL {

unsigned int Renderer::VAO = 0, Renderer::VBO = 0, Renderer::EBO = 0;
RenderList Renderer::renderList;
Renderer* instance = nullptr;

Renderer::Renderer() {
    instance = this;

    glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex colors
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::Destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Renderer* Renderer::get() {
    return instance;
}

void Renderer::Render() {
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, renderList.vertices.size() * sizeof(float), renderList.vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderList.indices.size() * sizeof(unsigned int), renderList.indices.data(), GL_DYNAMIC_DRAW);

    // Reset scissor to the full window size
    glScissor(0, 0, Application::width(), Application::height());

    // Enable the shader
    Shader* shader = ShaderManager::getShader("triangle");
    shader->use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Application::width()), 0.0f, static_cast<float>(Application::height()));
    shader->setMat4("projection", glm::value_ptr(projection));

    for (const RenderCommand& cmd : renderList.commands) {
        if (std::holds_alternative<DrawCommand>(cmd)) {
            const DrawCommand& drawCmd = std::get<DrawCommand>(cmd);
            glDrawElements(GL_TRIANGLES, drawCmd.idxCount, GL_UNSIGNED_INT, (void*)(drawCmd.idxOff * sizeof(unsigned int)));
        } else if (std::holds_alternative<CustomCallback>(cmd)) {
            const CustomCallback& customCmd = std::get<CustomCallback>(cmd);
            customCmd.callback(customCmd.data);

            // Assume the callback changed OpenGL state
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            shader->use();
            glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Application::width()), 0.0f, static_cast<float>(Application::height()));
            shader->setMat4("projection", glm::value_ptr(projection));
        } else if (std::holds_alternative<ScissorCommand>(cmd)) {
            const ScissorCommand& scissorCmd = std::get<ScissorCommand>(cmd);
            glScissor(scissorCmd.x, scissorCmd.y, scissorCmd.width, scissorCmd.height);
        }
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    renderList.commands.clear();
    renderList.vertices.clear();
    renderList.indices.clear();
}

}