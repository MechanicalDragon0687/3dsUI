
#include "gui/Container.hpp"
#include "gui/Element.hpp"
#include "gui/DataTypes.hpp"
#include <vector>
#include <string>

ContainerElement::~ContainerElement() { 
    for (Element* child:this->children) { 
        delete child; child=nullptr;
    }
}
ContainerElement::ContainerElement(Vector3f location, Vector2f size, std::string id, std::string groupId) : Element(location,size,id,groupId) { }
void ContainerElement::addChild(Element* e) { 
    e->setParent(this->parent); 
    e->setOffset(this->getLocationAbsolute());
    children.push_back(e); 
    this->markDirty();
}
bool ContainerElement::event(eventData data) {
    bool handled=false;
    for (int i=this->children.size()-1;i>=0;i--) {
        Element* child = this->children.at(i);
        if (data.global || child->isInside(TouchPosToVector(data.touch))) {
            handled = child->event(data);
        }
        if (handled && data.blockable) break;
    }
    if (!handled)
        handled=Element::event(data);
    return handled;
}
void ContainerElement::draw(Vector3f at) {
    for (Element* child : this->children)
        if (child->visible()) child->draw(at);
}
Element* ContainerElement::findById(std::string id) { 
    for (Element* child : this->children) {
        if (child->getId() == id) return child;
        Element* found = child->findById(id);
        if (found != nullptr)
            return found;
    }
    return nullptr;
}
void ContainerElement::setParent(Window* p) {
    this->parent=p;
    for (auto child:children) {
        child->setParent(p);
    }
}
void ContainerElement::setOffset(Vector3f offset) {
    Element::setOffset(offset);
    for (auto child:this->children)
        child->setOffset(this->getLocationAbsolute());
}
