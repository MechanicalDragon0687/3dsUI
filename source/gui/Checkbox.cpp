#include "gui/gui.hpp"
#include <citro2d.h>
#include <string>


Checkbox::Checkbox(Vector3f location, Vector2f size, float scale, std::string label, bool checked, std::string id) : ElementWithLabel(location,size,label,id) {
    this->scale=scale;
    this->checked=checked;
    this->registerListener({Click,[this](eventData d){this->checked=!this->checked; return true;}});
}
void Checkbox::draw(Vector3f at) {
    Vector3f loc = this->getLocationAbsolute();
    float z=at.z+loc.z;
    Vector2f minLoc = _asV2F((loc+at));
    Vector2f maxLoc = minLoc+this->size;
    drawBox(minLoc,maxLoc,z,CHECKBOX_BORDER,THEME_CHECKBOX_BORDER);
    if (this->checked) {
        C2D_DrawRectSolid(CHECKBOX_PADDING+minLoc.x+CHECKBOX_BORDER/2,CHECKBOX_PADDING+minLoc.y+CHECKBOX_BORDER/2,z,this->size.x-(CHECKBOX_PADDING*2+(CHECKBOX_BORDER)),this->size.y-(CHECKBOX_PADDING*2+(CHECKBOX_BORDER)),THEME_CHECKBOX_FILL);
    }
    drawText(_asV3F(minLoc,z)+Vector3f{this->size.x,0,0},{0,0},this->scale,0,0,CHECKBOX_TEXT," "+this->label);
}
