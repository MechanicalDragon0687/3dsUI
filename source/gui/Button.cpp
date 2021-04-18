#include <3ds.h>
#include "gui/gui.hpp"
#include <string>
#include <functional>


Button::Button(Vector3f Location, Vector2f size, std::string id, std::string label, std::function<bool(eventData)> onClick) : ElementWithLabel(Location,size,label,id) {
    if (onClick != nullptr)
        this->registerListener({Click, onClick});
}
Button::Button(Vector3f Location, std::string id, std::string label, std::function<bool(eventData)> onClick) : ElementWithLabel(Location, {0,0}, label, id) {
    this->label=label;
    Vector2f dim = getTextDimensions(label,TEXT_SCALE);
    this->size={dim.x+BUTTON_PADDING_RIGHT+BUTTON_PADDING_LEFT,dim.y+BUTTON_PADDING_TOP+BUTTON_PADDING_BOTTOM};
    if (onClick != nullptr)
        this->registerListener({Click, onClick});
}
void Button::draw(Vector3f at) {
    Vector3f loc = this->getLocationAbsolute();
    float z = at.z+loc.z;
    Vector2f minloc = _asV2F((at+loc));
    Vector2f maxloc = minloc+this->size;
    u32 color1=(!this->pressed)?THEME_BUTTON_BORDER1:THEME_BUTTON_BORDER2;
    u32 color2=(!this->pressed)?THEME_BUTTON_BORDER2:THEME_BUTTON_BORDER1;
    // button
    draw3dBox(minloc,maxloc,z+this->location.z,BUTTON_BORDER,THEME_BUTTON_BG,color1,color2);
    // label
    drawText({minloc.x+(this->size.x/2),minloc.y,z},this->size,TEXT_SCALE,C2D_AlignCenter | VALIGN_CENTER,0,THEME_BUTTON_TEXT,this->label);
}
