#pragma once
#include "DataTypes.hpp"
#include <string>

class Checkbox : public ElementWithLabel {
    protected:
        float scale;
        bool checked;
    public:
        Checkbox(Vector3f location, Vector2f size, float scale, std::string label, bool checked=false, std::string id="");
        void draw(Vector3f at);
};