#pragma once

#include "Style.h"

#include <string>
#include <memory>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

namespace IMGL {

typedef struct {
    unsigned int textureId; // ID handle of the glyph texture
    glm::ivec2 size;         // Size of glyph
    glm::ivec2 bearing;      // Offset from baseline to left/top of glyph
    unsigned int advance;    // Horizontal offset to advance to next glyph
} Character;

void FreeTypeInit();
void FreeTypeDone();

class Font {
public:
    Font(const std::string& fontPath, unsigned int fontSize);
    ~Font();

    void draw(const std::string& text, Color color, int x, int y);
    unsigned int getLineLength(const std::string& text);

private:
    FT_Face m_face;
    std::map<char, Character> m_characters;
    unsigned int m_VAO;
    unsigned int m_VBO;
};

class Text {
public:
    Text(const std::string& text, const std::string& fontPath, unsigned int fontSize, Color fontColor, int x, int y);
    ~Text();

    void draw();

private:
    std::string m_text;
    int m_x;
    int m_y;
	std::string m_fontPath;
	unsigned int m_fontSize;
    Color m_fontColor;
};

unsigned GetTextLength(const std::string& text);
void TextSize(unsigned int size);
void TextColor(const Color& color);
void DrawText(const std::string& text, int x, int y);
void DrawTextCallback(void* textObj);

}