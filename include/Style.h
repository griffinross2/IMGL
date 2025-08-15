#pragma once

namespace IMGL {

    // Style.h
    // This file contains the style definitions for the IMGL library.

    typedef struct {
        float r, g, b, a;
    } Color;

    // Default color definitions
    static const Color DefaultBackgroundColor = { 0.1f, 0.1f, 0.1f, 1.0f };

    static const Color DefaultContainerColor = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const Color DefaultContainerBorderColor = { 0.3f, 0.3f, 0.3f, 1.0f };
	static const unsigned int DefaultContainerBorderThickness = 2;

	static const Color DefaultTextColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const unsigned int DefaultTextSize = 16;
}