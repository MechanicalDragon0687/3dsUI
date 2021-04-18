#include "gui/Window.hpp"
#include "gui/ParentHolder.hpp"
ParentHolder::ParentHolder() {
    this->parent = nullptr;
}
void ParentHolder::markDirty() {
    if (parent!=nullptr)
        parent->markDirty();
}
Window* ParentHolder::getParent() {
    return this->parent;
}
void ParentHolder::setParent(Window* p) {
    this->parent=p;
}