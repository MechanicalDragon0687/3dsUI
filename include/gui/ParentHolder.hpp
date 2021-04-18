
#pragma once
class Window;
class ParentHolder { 
    protected:
        Window* parent;
    public:
        ParentHolder();
        virtual void markDirty();
        virtual Window* getParent();
        virtual void setParent(Window* p);
};