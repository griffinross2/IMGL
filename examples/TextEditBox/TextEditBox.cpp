#include "TextEditBox.h"

#include "Input.h"
#include "Text.h"
#include "Primitives.h"
#include "Container.h"
#include "Application.h"

#include <vector>

using namespace IMGL;

static std::vector<TextEditBox*> s_textEditBoxes;

TextEditBox::TextEditBox(const std::string& text, int x, int y, int width, int height) :
    m_text(text), m_x(x), m_y(y), m_width(width), m_height(height) {
    m_active = false;
    m_cursorPos = 0;
    m_cursorTime = 0.0f;
    m_selectionStart = 0;
    m_selectionEnd = 0;
    m_pressing = false;
    m_textSize = 20;

	s_textEditBoxes.push_back(this);
}

TextEditBox::~TextEditBox() {
    for (size_t i = 0; i < s_textEditBoxes.size(); i++) {
        if (s_textEditBoxes[i] == this) {
            s_textEditBoxes.erase(s_textEditBoxes.begin() + i);
            break;
        }
	}
}

void TextEditBox::draw() {
    // Get text starting point
    int tStartOff = 0;
    unsigned int textWidth, textHeight;
    TextSize(m_textSize);
    GetTextDimensions(m_text, textWidth, textHeight);
    if (textWidth > m_width - 10) {
        tStartOff = (m_width - 10) - textWidth;
    }

    // Check clicked
    int mx, my;
    unsigned int mousePosInText = 0;
    GetMousePosition(mx, my);
    for (size_t i = 1; i <= m_text.size(); i++) {
        mousePosInText = static_cast<int>(i - 1);
        GetTextDimensions(m_text.substr(0, i), textWidth, textHeight);
        if (mx - m_x - tStartOff - 5 < static_cast<int>(textWidth)) {
            break;
        }
        if (i == m_text.size()) {
            mousePosInText = m_text.size();
        }
    }

    // Check if click is inside
    MouseClick click = GetMouseClick();
    if (click.mouseLeftClick && CheckRectangleBounds(m_x, m_y, m_width, m_height, click.x, click.y)) {
        m_active = true;
        // If this click will move the cursor, reset the cursor time to immediately show the cursor
        if (m_cursorPos != mousePosInText) {
            m_cursorTime = 0.0;
        }
        m_cursorPos = mousePosInText;
        
    }
    else if (click.mouseLeftClick) {
        m_active = false;
    }

    // Check for drag selection
    bool leftButton, rightButton, middleButton;
    GetMouseButton(leftButton, rightButton, middleButton);
    if (!m_pressing && leftButton && CheckRectangleBounds(m_x, m_y, m_width, m_height, mx, my)) {
        m_pressing = true;
        m_selectionStart = mousePosInText;
    }
    if (m_pressing && leftButton) {
        m_selectionEnd = mousePosInText;
    }
    if (m_pressing && !leftButton) {
        m_pressing = false;
    }

    // Draw background and border
    // Use container for clipping purposes
	ContainerBackground(Color{ 0.2f, 0.2f, 0.2f, 1.0f });
	ContainerBorderColor(Color{ 1.0f, 1.0f, 1.0f, 1.0f });
    ContainerBorderThickness(2);
    ContainerBegin(m_x, m_y, m_width, m_height);

    // Draw selection highlight
    if (m_selectionStart != m_selectionEnd) {
        int selStart = std::min(m_selectionStart, m_selectionEnd);
        int selEnd = std::max(m_selectionStart, m_selectionEnd);
        unsigned int selXStart, selXEnd;
        GetTextDimensions(m_text.substr(0, selStart), selXStart, textHeight);
        GetTextDimensions(m_text.substr(0, selEnd), selXEnd, textHeight);
        DrawRectangle(5 + tStartOff + selXStart, (m_height - m_textSize) / 2, selXEnd - selXStart, m_textSize, Color{ 0.4f, 0.4f, 0.8f, 1.0f });
    }

    // Draw text
    GetTextDimensions(m_text, textWidth, textHeight);
    if (textWidth > m_width - 10) {
        DrawText(m_text, 5 + tStartOff, (m_height - textHeight) / 2);
    } else {
        DrawText(m_text, 5 + tStartOff, (m_height - textHeight) / 2);
    }

    // Draw cursor if active
    if (m_active) {
        // Simple cursor blink
        if (static_cast<int>(m_cursorTime * 2.0) % 2 == 0) {
            // Calculate cursor position
            unsigned int cursorX;
            GetTextDimensions(m_text.substr(0, m_cursorPos), cursorX, textHeight);
            DrawRectangle(5 + cursorX + tStartOff, (m_height - m_textSize) / 2, 1, m_textSize, Color{ 1.0f, 1.0f, 1.0f, 1.0f });
        }
        m_cursorTime += Application::deltaTime();
        if (m_cursorTime > 1.0) {
            m_cursorTime = 0.0;
        }
    }

	ContainerEnd();
}

void TextEditBox::keyEventCallback(int key, int action, int mod) {
    if (key == GLFW_KEY_LEFT && m_active && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // Move cursor left
        if (m_cursorPos > 0) {
            m_cursorTime = 0.0; // Reset cursor blink so its visible immediately
            m_cursorPos--;
            m_selectionEnd = m_cursorPos;
        }
        if (!(mod & GLFW_MOD_SHIFT)) {
            m_selectionStart = m_cursorPos;
        }
    }
    if (key == GLFW_KEY_RIGHT && m_active && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // Move cursor right
        if (m_cursorPos < static_cast<int>(m_text.size())) {
            m_cursorTime = 0.0; // Reset cursor blink so its visible immediately
            m_cursorPos++;
            m_selectionEnd = m_cursorPos;
        }
        if (!(mod & GLFW_MOD_SHIFT)) {
            m_selectionStart = m_cursorPos;
        }
    }
    if (key == GLFW_KEY_BACKSPACE && m_active && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // Delete selection or delete character before cursor
        if (!deleteSelection() && m_cursorPos > 0) {
            m_text.erase(m_cursorPos - 1, 1);
            m_cursorPos--;
            m_selectionStart = m_cursorPos;
            m_selectionEnd = m_cursorPos;
        }
    }
    if (key == GLFW_KEY_DELETE && m_active && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // Delete selection or delete character after cursor
        if (!deleteSelection() && m_cursorPos < static_cast<int>(m_text.size())) {
            m_text.erase(m_cursorPos, 1);
            m_selectionStart = m_cursorPos;
            m_selectionEnd = m_cursorPos;
        }
    }
    if (key == GLFW_KEY_A && m_active && action == GLFW_PRESS && (mod & GLFW_MOD_CONTROL)) {
        // Select all text
        m_selectionStart = 0;
        m_selectionEnd = static_cast<int>(m_text.size());
		m_cursorPos = m_selectionEnd;
    }
}
  
void TextEditBox::charEventCallback(unsigned int codepoint) {
    if (m_active) {
        // If there is a selection, delete it first
        deleteSelection();
        // Insert the character at the cursor position
        m_text.insert(m_cursorPos, 1, static_cast<char>(codepoint));
        m_cursorPos++;
        m_selectionStart = m_cursorPos;
        m_selectionEnd = m_cursorPos;
    }
}

void textEditBoxKeyEventCallback(int key, int action, int mod) {
    for (TextEditBox* boxPtr : s_textEditBoxes) {
        boxPtr->keyEventCallback(key, action, mod);
	}
}

void textEditBoxCharEventCallback(unsigned int codepoint) {
    for (TextEditBox* boxPtr : s_textEditBoxes) {
        boxPtr->charEventCallback(codepoint);
    }
}

bool TextEditBox::deleteSelection() {
    if (m_selectionStart != m_selectionEnd) {
        int selStart = std::min(m_selectionStart, m_selectionEnd);
        int selEnd = std::max(m_selectionStart, m_selectionEnd);
        m_text.erase(selStart, selEnd - selStart);
        m_cursorPos = selStart;
        m_selectionStart = selStart;
        m_selectionEnd = selStart;
        return true;
    }
    return false;
}