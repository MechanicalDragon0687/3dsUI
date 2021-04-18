#pragma once
#include "DataTypes.hpp"
#include <string>

enum {
    VALIGN_TOP =        0 << 8,
    VALIGN_CENTER =     1 << 8,
    VALIGN_BOTTOM =     1 << 9
};

void drawBox(Vector2f topLeft, Vector2f bottomRight, float z, float thickness, u32 color1, u32 color2);
void drawBox(Vector2f topLeft, Vector2f bottomRight, float z, float thickness, u32 color1);
void draw3dBox(Vector2f topLeft, Vector2f bottomRight, float z, float thickness, u32 bg, u32 border1, u32 border2);
void drawText(Vector3f location, Vector2f size, float scale, u32 flags, u32 bgColor, u32 color, std::string label);