#include "Primitives.h"

#include "Render.h"
#include "Container.h"

namespace IMGL {

    void DrawRectangle(int x, int y, int width, int height, const Color& color) {
        // Convert coordinates to screen space
        ToScreenSpace(x, y);

        // Draw the rectangle
        RenderList& renderList = Renderer::get()->renderList;
        unsigned int firstIdx = renderList.vertices.size() / 7;
        unsigned int idxOff = renderList.indices.size();

        // Bottom Left
        renderList.vertices.push_back(static_cast<float>(x));
        renderList.vertices.push_back(static_cast<float>(y));
        renderList.vertices.push_back(0.0f); // z-coordinate
        renderList.vertices.push_back(color.r);
        renderList.vertices.push_back(color.g);
        renderList.vertices.push_back(color.b);
        renderList.vertices.push_back(color.a);

        // Bottom Right
        renderList.vertices.push_back(static_cast<float>(x + width));
        renderList.vertices.push_back(static_cast<float>(y));
        renderList.vertices.push_back(0.0f); // z-coordinate
        renderList.vertices.push_back(color.r);
        renderList.vertices.push_back(color.g);
        renderList.vertices.push_back(color.b);
        renderList.vertices.push_back(color.a);

        // Top Right
        renderList.vertices.push_back(static_cast<float>(x + width));
        renderList.vertices.push_back(static_cast<float>(y + height));
        renderList.vertices.push_back(0.0f); // z-coordinate
        renderList.vertices.push_back(color.r);
        renderList.vertices.push_back(color.g);
        renderList.vertices.push_back(color.b);
        renderList.vertices.push_back(color.a);

        // Top Left
        renderList.vertices.push_back(static_cast<float>(x));
        renderList.vertices.push_back(static_cast<float>(y + height));
        renderList.vertices.push_back(0.0f); // z-coordinate
        renderList.vertices.push_back(color.r);
        renderList.vertices.push_back(color.g);
        renderList.vertices.push_back(color.b);
        renderList.vertices.push_back(color.a);

        // Add indices for the rectangle (two triangles)
        renderList.indices.push_back(firstIdx);
        renderList.indices.push_back(firstIdx + 1);
        renderList.indices.push_back(firstIdx + 2);
        renderList.indices.push_back(firstIdx);
        renderList.indices.push_back(firstIdx + 2);
        renderList.indices.push_back(firstIdx + 3);

        // Add a draw command for the rectangle
        DrawCommand drawCmd;
        drawCmd.idxOff = idxOff;
        drawCmd.idxCount = 6; // Two triangles, 6 indices
        renderList.commands.push_back(drawCmd);
    }

    bool CheckRectangleBounds(int x, int y, int width, int height, int pointX, int pointY) {
        // Convert rectangle coordinates to screen space
        ToScreenSpace(x, y);
        return (pointX >= x) && (pointX <= x + width) &&
               (pointY >= y) && (pointY <= y + height);
	}

    void DrawLine(int x1, int y1, int x2, int y2, const Color& color, unsigned int thickness) {
    }

    void DrawBorder(int x, int y, int width, int height, const Color& color, unsigned int thickness) {
        // Draw bottom border
		DrawRectangle(x, y, width, thickness, color);
		// Draw top border
		DrawRectangle(x, y + height - thickness, width, thickness, color);
		// Draw left border
		DrawRectangle(x, y, thickness, height, color);
		// Draw right border
		DrawRectangle(x + width - thickness, y, thickness, height, color);
	}

}
