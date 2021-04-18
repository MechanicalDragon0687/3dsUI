#include "gui/Panel.hpp"
#include "gui/DataTypes.hpp"
#include "gui/Container.hpp"
#include "gui/Element.hpp"
#include "gui/Theme.hpp"
#include "gui/drawingHelper.hpp"

#include <string>

Panel::Panel(Vector3f location, Vector2f size, std::string id, std::string label, uint32_t flags) : ContainerElement(location,size,id) {
    this->flags=flags;
    this->label = label;
}
void Panel::setLabel(std::string label) {
    this->label=label;
}
void Panel::addChild(Element* e) { 
    e->setParent(this->parent); 
    e->setOffset(this->getLocationAbsolute()+Vector3f{PANEL_PADDING_LEFT+PANEL_MARGIN+PANEL_BORDER,PANEL_PADDING_TOP+PANEL_MARGIN+PANEL_BORDER,0});
    this->children.push_back(e); 
}
void Panel::draw(Vector3f location) {
    Vector3f loc = this->getLocationAbsolute();
    Vector2f topLeft = _asV2F((loc+location))+Vector2f{PANEL_MARGIN,PANEL_MARGIN};
    Vector2f bottomRight = topLeft+this->size-Vector2f{PANEL_MARGIN*2,PANEL_MARGIN*2};
    draw3dBox(topLeft, bottomRight, location.z+loc.z, PANEL_BORDER, THEME_PANEL_BG, THEME_PANEL_BORDER1, THEME_PANEL_BORDER2);
    if (!this->label.empty())
        drawText({loc.x+(this->size.x/2),loc.y,loc.z}, {this->size.x,PANEL_BORDER+PANEL_MARGIN*2}, TEXT_SCALE, C2D_AlignCenter | VALIGN_CENTER, THEME_PANEL_BG, THEME_PANEL_TEXT, this->label);
    ContainerElement::draw(location);
}
