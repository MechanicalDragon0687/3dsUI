#pragma once
#include "Element.hpp"
#include <functional>
#include <string>


class Button: public ElementWithLabel {
    public:
        Button(Vector3f Location, Vector2f size, std::string id, std::string label, std::function<bool(eventData)> onClick);
        Button(Vector3f Location, std::string id, std::string label, std::function<bool(eventData)> onClick);
        void draw(Vector3f at);
};