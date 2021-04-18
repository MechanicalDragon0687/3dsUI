#include "gui/Window.hpp"
#include "gui/Element.hpp"

#include <vector>
#include <string>

#include <citro2d.h>
#include "gui/Inputs.hpp"

bool WINDOW_REVERSE_SENDEVENTS(std::vector<Element*>* vec,eventData data ) {
    bool handled=false;
    for (int i=vec->size()-1;i>=0;i--) {
        Element* child = vec->at(i);
        if (data.global || child->isInside(TouchPosToVector(data.touch))) {
            handled = child->event(data);
        }else{
            if (data.type != TouchMove) child->isInside(TouchPosToVector(data.touch),true);
        }
        if (handled && data.blockable) break;
    }
    return handled;
}
Window::Window(WindowData* data) {
    this->wData=data;
    this->focus=nullptr;
    this->dirty=true;
}

void Window::addChild(Element* e) {
    e->setParent(this); 
    this->children.push_back(e);
    this->markDirty();
}
void Window::setFocus(Element* focus) { 
    this->focus = focus; 
    this->toTop(focus);
}
void Window::removeChild(Element* e, bool del) {
    if (del)
        delete e; 
    std::remove_if(this->children.begin(),this->children.end(),[](Element* el){
        return el==nullptr;
    });
    this->markDirty();
}
void Window::toTop(Element* e) {
    removeChild(e,false);
    this->addChild(e);
}
void Window::draw() {
    if (this->isDirty()) {
        C2D_TargetClear(this->wData->target, this->wData->bgColor);
        C2D_SceneBegin(this->wData->target);
        for (Element* e:this->children) {
            if (e->visible()) e->draw({0,0,0});
        }
        this->clearDirty();
    }
}
void Window::handleInput(inputData* input) {
    if ((input->kDown & KEY_TOUCH)>0) {
        WINDOW_REVERSE_SENDEVENTS(&this->children,{TouchDown,KEY_TOUCH,{input->mouseX,input->mouseY}});
    }else if((input->kHeld & KEY_TOUCH)>0) {
        WINDOW_REVERSE_SENDEVENTS(&this->children,{TouchMove,KEY_TOUCH,{input->mouseX,input->mouseY},false, true});
    }else if((input->kUp & KEY_TOUCH)>0) {
        WINDOW_REVERSE_SENDEVENTS(&this->children,{TouchUp,KEY_TOUCH,{input->mouseX,input->mouseY},false});
    }
    if ((input->kDown & ~KEY_TOUCH)>0) {
        if (this->focus!=nullptr && this->focus->visible()) {
            eventData d = {eventType::KeyDown,input->kDown,{0,0},false,false};
            this->focus->event(d);
        }
    }
}
void Window::markDirty() { this->dirty=true; }
bool Window::isDirty() { return this->dirty;}
void Window::clearDirty() { this->dirty=false;}
Element* Window::findById(std::string id) { 
    for (Element* child : this->children) {
        if (child->getId() == id) return child;
        void* found = child->findById(id);
        if (found != nullptr)
            return static_cast<Element*>(found);
    }
    return nullptr;
}
