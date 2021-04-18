#pragma once

#include <string>
#include "DataTypes.hpp"
#include "Container.hpp"

#define PANEL_FLAG_ALIGN_CENTER     0
#define PANEL_FLAG_ALIGN_LEFT       1
#define PANEL_FLAG_ALIGN_RIGHT      1<<1


class Panel : public ContainerElement {
    protected:
        uint32_t flags;
        std::string label;
    public:
        Panel(Vector3f location, Vector2f size, std::string id = "", std::string label="", uint32_t flags=0);
        virtual void setLabel(std::string label);
        virtual void addChild(Element* e);
        virtual void draw(Vector3f location);
};
