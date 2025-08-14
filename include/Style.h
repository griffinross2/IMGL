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
}