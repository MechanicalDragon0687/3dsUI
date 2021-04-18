#pragma once
#include <vector>
#include <string>
#include <citro3d.h>
#include "Element.hpp"
#include "Inputs.hpp"



typedef struct {
    C3D_RenderTarget* target;
    float width;
    float height;
    uint32_t bgColor;
}WindowData;

#define KEY_DIR (KEY_LEFT | KEY_RIGHT | KEY_UP | KEY_DOWN)

class Window {
    protected:
        bool dirty=true;
        WindowData* wData;
        std::vector<Element*> children;
        Element* focus;
    public:
    Window(WindowData* data);
    
    void addChild(Element* e);
    void setFocus(Element* focus);
    void removeChild(Element* e, bool del = true);
    void toTop(Element* e);
    void draw();
    void handleInput(inputData* input);
    void markDirty();
    bool isDirty();
    void clearDirty();
    Element* findById(std::string id);
};