#include "gui/FileEntry.hpp"
#include "gui/Container.hpp"
#include "gui/FileSelector.hpp"
#include "gui/Label.hpp"
#include "gui/Button.hpp"
#include "gui/font.hpp"
#include <filesystem>
#include <string>

FileEntry::FileEntry(Vector3f location, Vector2f size, FileSelector* fs, std::string filter, std::string id) : ContainerElement(location,size,id) {
    //TODO: configurable padding
    Label* locationlabel = new Label({10,size.y/2,0},0.55,"",VALIGN_CENTER,this->id+".locationLabel");
    this->fs = fs;
    Vector2f textDefaultSize = getTextDimensions("W",0.55);
    uint16_t maxChars = (size.x-40-10-10)/textDefaultSize.x;
    this->addChild(locationlabel);
    fs->registerListener({Close,
        [this,locationlabel,fileSelector=this->fs,filter,maxChars](eventData data){
            this->entry = fileSelector->getSelected();
            std::string sLabel = "";
            if (this->entry.is_directory()) {
                sLabel = fileSelector->getSelected().path();
                if (*(sLabel.end()-1)!='/') sLabel+="/";
                sLabel += "*."+filter;
            }else{
                sLabel = fileSelector->getSelected().path().filename().generic_string();
            }

            if (sLabel.size() > maxChars) {
                sLabel = "..."+sLabel.substr(sLabel.size()-maxChars-3);
            }
            locationlabel->setLabel(sLabel);
            return true;
        }
    });
    Button* b = new Button({size.x-40-10,size.y/2-(20/2),0},{40,20},"buttonTest","...",
        [this,locationlabel,fs, filter](eventData data){
            this->entry=std::filesystem::directory_entry();
            locationlabel->setLabel("");
            fs->setFilter(filter);
            fs->getParent()->setFocus(fs); 
            fs->show(); 
            return true;
        }
    );
    this->addChild(b);
}
