#pragma once

typedef struct {
    uint16_t mouseX;
    uint16_t mouseY;
    uint32_t kDown;
    uint32_t kUp;
    uint32_t kHeld;
    uint32_t kRepeat;
    void* DraggedElement;
} inputData;

