#pragma once
#include "Element.hpp"
#include "Container.hpp"
#include "drawingHelper.hpp"
#include "Theme.hpp"
#include "font.hpp"
#include <string>
#include <citro2d.h>
#include <any>
class ListEntry : public ContainerElement {
    protected:
        std::any data;
        float scale;
        std::string label;

    public:
    ListEntry(Vector2f size, float scale, std::string label, std::any data, std::string id) : ContainerElement({0,0,0},size,id) {
        this->data=data;
        this->scale = scale;
        this->label = label;
    }
    void setLabel(std::string label) {
        this->label = label;
        this->markDirty();
    }
    void draw(Vector3f at) {
        this->draw(at,false);
    }
    void draw(Vector3f at, bool selected) {
        Vector2f topLeft = _asV2F(at);
        Vector2f bottomRight = topLeft+this->size;
        C2D_DrawRectSolid(topLeft.x,topLeft.y,at.z,this->size.x,this->size.y,(selected)?THEME_LIST_ENTRY_HIGHLIGHT:THEME_LIST_ENTRY_BG);
        C2D_DrawLine(topLeft.x,topLeft.y,THEME_LIST_ENTRY_BORDER,bottomRight.x,topLeft.y,THEME_LIST_ENTRY_BORDER,1,at.z);
        Vector3f textLoc = {topLeft.x + LIST_ENTRY_PADDING_LEFT, topLeft.y , at.z};
        
        drawText(textLoc,{0,this->size.y},this->scale,VALIGN_CENTER,0,(selected)?THEME_LIST_ENTRY_HIGHLIGHT_TEXT:THEME_LIST_ENTRY_TEXT,this->label);
        ContainerElement::draw(at);
    }
    std::any getData() { return this->data; }
};
