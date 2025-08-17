#include "Text.h"

#include "Application.h"
#include "Style.h"
#include "Container.h"
#include "Shader.h"

#include <stdexcept>

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace IMGL {

    // Define a structure to cache fonts
    typedef struct FontDescriptor {
		std::string fontPath;
		unsigned int fontSize;

        bool const operator==(const FontDescriptor& o) {
			return fontPath == o.fontPath && fontSize == o.fontSize;
        }

        bool const operator<(const FontDescriptor& o) const {
            return fontPath.compare(o.fontPath) < 0 || fontSize < o.fontSize;
        }
    } FontDescriptor;

    // Font cache map
    static std::map<FontDescriptor, std::shared_ptr<Font>> s_fontCache;

    static FT_Library s_ft = nullptr;

    static unsigned int s_fontSize = DefaultTextSize;
    static Color s_fontColor = DefaultTextColor;

    void FreeTypeInit() {
        if (s_ft == nullptr) {
            if (FT_Init_FreeType(&s_ft)) {
                throw std::runtime_error("Could not initialize FreeType library");
            }
        }
    }

    void FreeTypeDone() {
        if (s_ft) {
            FT_Done_FreeType(s_ft);
            s_ft = nullptr;
        }
    }

    Font::Font(const std::string& fontPath, unsigned int fontSize) {
        // Configure VAO/VBO for texture quads
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Initialize FreeType if not already done
        FreeTypeInit();

        // Initialize the font face
        if (FT_New_Face(s_ft, fontPath.c_str(), 0, &m_face)) {
            throw std::runtime_error("Could not load font face from " + fontPath);
        }
        if (FT_Set_Pixel_Sizes(m_face, 0, fontSize)) {
            throw std::runtime_error("Could not set pixel size for font face");
        }

        // Byte-alignment
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Load all ASCII characters
        for (unsigned char c = 0; c < 128; c++) {
            // Load character glyph
            if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
                throw std::runtime_error("Could not load character " + std::string(1, c));
            }

            // Generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                m_face->glyph->bitmap.width,
                m_face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                m_face->glyph->bitmap.buffer
            );
            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Store character for later use
            Character character = {
                texture,
                glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
                glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
                static_cast<unsigned int>(m_face->glyph->advance.x)
            };
            m_characters.insert(std::pair<char, Character>(c, character));
        }
    }

    Font::~Font() {
        // Delete character textures
        for (auto& pair : m_characters) {
            glDeleteTextures(1, &pair.second.textureId);
        }
        // Delete VAO/VBO
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        // Delete font face
		FT_Done_Face(m_face);
    }

    void Font::draw(const std::string& text, Color color, int x, int y) {
        // Bind things
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(IMGL::Application::width()), 0.0f, static_cast<float>(IMGL::Application::height()));
        Shader* shader = IMGL::ShaderManager::getShader("text");
        shader->use();
        shader->setVec3("textColor", color.r, color.g, color.b);
        shader->setMat4("projection", glm::value_ptr(projection));

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(m_VAO);

        float d_x = static_cast<float>(x);
        float d_y = static_cast<float>(y);

        // Draw each character
        for (char c : text) {
            // Quad dimensions
            Character ch = m_characters.at(c);
            float xpos = d_x + ch.bearing.x;
            float ypos = d_y - (ch.size.y - ch.bearing.y);
            float w = ch.size.x;
            float h = ch.size.y;

            // Get vertices
            float vertices[6][4] = {
                { xpos,     ypos + h, 0.0f, 0.0f },
                { xpos + w, ypos,     1.0f, 1.0f },
                { xpos,     ypos,     0.0f, 1.0f },

                { xpos,     ypos + h, 0.0f, 0.0f },
                { xpos + w, ypos + h, 1.0f, 0.0f },
                { xpos + w, ypos,     1.0f, 1.0f }
            };

            // Bind texture
            glBindTexture(GL_TEXTURE_2D, ch.textureId);

            // Update VBO
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Draw
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Advance
            d_x += (ch.advance >> 6);
        }

        // Unbind
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Font::getLineDimensions(const std::string& text, unsigned int& width, unsigned int& height) {
        unsigned int lineWidth = 0;
        unsigned int lineHeight = 0;
        for (char c : text) {
            lineWidth += m_characters.at(c).advance >> 6;
            if (m_characters.at(c).size.y > lineHeight) {
                lineHeight = m_characters.at(c).size.y;
            }
        }
		width = lineWidth;
		height = lineHeight;
    }

    Text::Text(const std::string& text, const std::string& fontPath, unsigned int fontSize, Color fontColor, int x, int y)
        : m_text(text), m_fontPath(fontPath), m_fontSize(fontSize), m_fontColor(fontColor), m_x(x), m_y(y) {
        // Ensure the font is cached
        if (s_fontCache.find({ fontPath, fontSize }) == s_fontCache.end()) {
            s_fontCache[{ fontPath, fontSize }] = std::make_shared<Font>(fontPath, fontSize);
        }
	}

    Text::~Text() {
	}

    void Text::draw() {
		std::shared_ptr<Font> fontPtr = s_fontCache[{m_fontPath, m_fontSize}];
		fontPtr->draw(m_text, m_fontColor, m_x, m_y);
    }

    void GetTextDimensions(const std::string& text, unsigned int& width, unsigned int& height) {
        // Ensure the font exists
        if (s_fontCache.find({ "fonts/Roboto/static/Roboto-Regular.ttf", s_fontSize }) == s_fontCache.end()) {
            s_fontCache[{ "fonts/Roboto/static/Roboto-Regular.ttf", s_fontSize }] = std::make_shared<Font>("fonts/Roboto/static/Roboto-Regular.ttf", s_fontSize);
		}

		return s_fontCache[{ "fonts/Roboto/static/Roboto-Regular.ttf", s_fontSize }]->getLineDimensions(text, width, height);
	}

    void TextSize(unsigned int size) {
        s_fontSize = size;
    }

    void TextColor(const Color& color) {
        s_fontColor = color;
    }

    void DrawText(const std::string& text, int x, int y) {
		ToScreenSpace(x, y);

        // Create a Text object and add a draw callback to the render list
        Text* textObj = new Text(text, "fonts/Roboto/static/Roboto-Regular.ttf", s_fontSize, s_fontColor, static_cast<int>(x), static_cast<int>(y));
        IMGL::CustomCallback callback = {
            .callback = DrawTextCallback,
            .data = static_cast<void*>(textObj),
        };
        IMGL::Renderer::get()->renderList.commands.push_back(callback);
    }

    void DrawTextCallback(void* textObj) {
        Text* text = static_cast<Text*>(textObj);

        text->draw();

        // Make sure to delete the text object
        delete text;
    }

}