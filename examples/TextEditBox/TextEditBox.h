#pragma once

#include <string>

void textEditBoxKeyEventCallback(int key, int action, int mod);
void textEditBoxCharEventCallback(unsigned int codepoint);

class TextEditBox {

public:
    TextEditBox(const std::string& text, int x, int y, int width, int height);
    ~TextEditBox();

    void draw();

	void keyEventCallback(int key, int action, int mod);
    void charEventCallback(unsigned int codepoint);

private:
    std::string m_text;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    bool m_active;
    int m_cursorPos;
    int m_selectionStart;
    int m_selectionEnd;
    bool m_pressing;
    int m_textSize;
};