#pragma once
#include <3ds.h>
#include "DataTypes.hpp"
#include "Inputs.hpp"
#include "ParentHolder.hpp"
#include "Theme.hpp"
#include <functional>
#include <string>
#include <vector>
#include <map>
#define TypeOf(object, type) (type* tmpType = dynamic_cast< type* >( &object ) )
#define TouchPosToVector(tp) (Vector2f{static_cast<float>(tp.px),static_cast<float>(tp.py)})
enum eventType {
    KeyDown,
    KeyUp,
    TouchDown,
    TouchUp,
    TouchMove,
    Click,
    Close
};

typedef struct {
    eventType type;
    u32 key;
    touchPosition touch;
    bool blockable;
    bool global;
} eventData;

typedef struct {
    eventType type;
    std::function<bool(eventData)> callback;
}listener;
class Element;
class Element : public ParentHolder {
    protected:
        Vector3f location;
        Vector3f offset;
        Vector2f size;
        bool _visible=true;
        std::string groupId;
        std::string id;
        bool pressed;
        std::vector<listener> listeners;
    public:
        Element(Vector3f location, Vector2f size, std::string id="", std::string groupId="");
        //Element(float x,float y, float z, float width, float height, std::string id="", std::string groupId=""):Element({x,y,z},{width,height},id,groupId){ };
        virtual ~Element();

        virtual void hide();
        virtual void show();
        virtual bool visible();
        virtual void setVisible(bool visible);
        virtual Vector3f getLocationAbsolute();
        virtual Vector3f getLocationRelative();
        virtual Vector2f getSize();
        virtual void setSize(Vector2f size);
        virtual void setWidth(float x);
        virtual void setHeight(float y);
        std::string getId();
        virtual void setOffset(Vector3f offset);
        virtual void draw(Vector3f at);
        virtual bool event(eventData data);
        virtual bool _default_handleEvent(eventData data);
        virtual void registerListener(listener l);
        virtual bool isInside(Vector2f at, bool log=false);
        virtual Element* findById(std::string id);
};

class ElementWithLabel : public Element {
    protected:
        std::string label;
    public:
        ElementWithLabel(Vector3f location, Vector2f size, std::string label, std::string id="", std::string groupId="");
        virtual std::string getLabel();
        virtual void setLabel(std::string s);
};
