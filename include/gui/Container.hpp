#pragma once

#include "Element.hpp"
#include "Theme.hpp"
#include "Window.hpp"
#include "DataTypes.hpp"

#include <vector>
#include <string>

class ContainerElement : public Element {
    protected:
        std::vector<Element*> children;
    public:
        ~ContainerElement();
        ContainerElement(Vector3f location, Vector2f size, std::string id="", std::string groupId="" );
        virtual void addChild(Element* e);
        virtual bool event(eventData data);
        virtual void draw(Vector3f at);
        virtual Element* findById(std::string id);
        virtual void setParent(Window* p);
        virtual void setOffset(Vector3f offset);
};