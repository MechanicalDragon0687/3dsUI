#pragma once
#include "Button.hpp"
#include "ResultProvider.hpp"

class DialogButton : public Button {
    protected:
        ResultProvider* results;
        int value = -1;
    public:
    DialogButton(ResultProvider* p, int value, Vector3f Location, Vector2f size, std::string id, std::string label);
    DialogButton(ResultProvider* p, int value, Vector3f Location, std::string id, std::string label);
    void setResults(int i);
};