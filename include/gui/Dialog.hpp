#pragma once
#include "Panel.hpp"
#include "ResultProvider.hpp"
#include <vector>
#include <string>
#include <functional>


class Dialog : public Panel, public ResultProvider {
    protected:
    public:
    Dialog(Vector3f location, Vector2f size, std::string id, std::string label, std::string message, std::vector<std::string> buttons, std::function<void(int)> onComplete);
    void setResult(int i);
};