#include <functional>
#include <vector>
#include <map>
#include <string>
#include <3ds.h>
#include "gui/gui.hpp"

Element::Element(Vector3f location, Vector2f size, std::string id, std::string groupId) {
            this->location = location;
            this->size = size;
            this->offset={0,0,0};
            this->id=id;
            this->groupId=groupId;
            this->pressed = false;
            this->parent = nullptr;
        }
Element::~Element() {}

void Element::hide() { this->setVisible(false);}
void Element::show() { this->setVisible(true);}
bool Element::visible() { return this->_visible; }
void Element::setVisible(bool visible) {
    this->_visible = visible;
    this->markDirty();
}
Vector3f Element::getLocationAbsolute(){ return {this->location.x+this->offset.x,this->location.y+this->offset.y,this->location.z+this->offset.z}; }
Vector3f Element::getLocationRelative(){ return this->location; }
Vector2f Element::getSize(){ return this->size; }
void Element::setSize(Vector2f size) {
    this->size = size;
}
void Element::setWidth(float x) {
    this->size = {x,this->size.y};
}
void Element::setHeight(float y) {
    this->size = {this->size.x,y};
}
std::string Element::getId() {return this->id;}
void Element::setOffset(Vector3f offset) { this->offset = offset; }
void Element::draw(Vector3f at) { }
bool Element::event(eventData data) { 
    if (!this->visible()) return false;
    bool handled = false;
    for (listener l : this->listeners) {
        if (l.type == data.type) {
            handled = l.callback(data);
            if (handled & data.blockable) break;
        }
    }
    if (!handled)
        return _default_handleEvent(data);
    return handled;
}; 
bool Element::_default_handleEvent(eventData data) { 
    bool handled = false;
    switch (data.type) {
        case TouchDown:
            if (this->isInside(TouchPosToVector(data.touch))) {
                this->pressed=true;
                this->markDirty();
            }
            break;
        case TouchUp:
            if (this->isInside(TouchPosToVector(data.touch))) {
                if (this->pressed) {
                    handled = this->event({Click,data.key,data.touch});
                    this->pressed=false;
                    this->markDirty();
                }
                
            }
            break;
        case TouchMove:
            if(!this->isInside(TouchPosToVector(data.touch)) && this->pressed) {
                this->pressed=false;
                this->markDirty();
            }
            break;
        default:
            break;
    }
    return handled; 
}
void Element::registerListener(listener l) { this->listeners.push_back(l); }
bool Element::isInside(Vector2f at, bool log) { 
    if (!this->visible())
        return false;
    Vector2f locMin = _asV2F(this->getLocationAbsolute());
    Vector2f locMax = locMin+this->size;
    return locMin <= at && at <= locMax;
}
Element* Element::findById(std::string id) { return nullptr;}


ElementWithLabel::ElementWithLabel(Vector3f location, Vector2f size, std::string label, std::string id, std::string groupId) : Element(location, size, id) { 
    this->label = label; 
}
std::string ElementWithLabel::getLabel() {return this->label;}
void ElementWithLabel::setLabel(std::string s) { this->label = s; this->markDirty(); }

