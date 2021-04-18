#pragma once
#include "Element.hpp"
#include "DataTypes.hpp"
#include <string>

class Label : public ElementWithLabel {
    protected:
        float scale;
        uint32_t flags;
        uint32_t clr;
    public:
    Label(Vector3f location, float scale, std::string label, uint32_t flags=0, std::string id="");
    virtual void setColor(u32 color);
    void draw(Vector3f at);
    virtual void setLabel(std::string label);
};