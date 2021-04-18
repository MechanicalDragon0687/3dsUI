#include "gui/DialogButton.hpp"
#include "gui/Button.hpp"
#include "gui/ResultProvider.hpp"

DialogButton::DialogButton(ResultProvider* p, int value, Vector3f Location, Vector2f size, std::string id, std::string label) : Button(Location, size, id, label, nullptr) { 
    this->results=p;
    this->registerListener({Click,[this](eventData data){this->setResults(this->value);return true;}});
}
DialogButton::DialogButton(ResultProvider* p, int value, Vector3f Location, std::string id, std::string label) : Button(Location, id, label, nullptr) {
    this->results=p;
    this->registerListener({Click,[this](eventData data){this->setResults(this->value);return true;}});
}
void DialogButton::setResults(int i) {
    results->setResult(i);
}
