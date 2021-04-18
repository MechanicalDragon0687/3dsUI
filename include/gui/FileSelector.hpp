#pragma once
#include "Panel.hpp"
#include <vector>
#include <regex>
#include <filesystem>
#include <locale>
#include <string>
#include "ListEntry.hpp"
#define toLower(s) std::transform(s.begin(), s.end(), s.begin(), [](char c){return std::tolower(c);})
#define ENTRIES_PER_SCREEN 5

bool sortMenuSelections(std::filesystem::directory_entry a, std::filesystem::directory_entry b);
class FileSelector : public Panel {
    protected:
        std::vector<ListEntry*> entries;
        std::vector<ListEntry*>::iterator selection;
        std::vector<ListEntry*>::iterator top;
        std::regex filter;
        std::filesystem::path cwd;
        bool selected;
        bool selectFolder;
        virtual bool canSelectFolder(std::vector<std::filesystem::directory_entry>* dirEntries);
    public:
    FileSelector(Vector3f location, Vector2f size, std::string id = "", std::string label="", uint32_t flags=0, std::string filter="*", bool canSelectFolder=true);
    virtual std::filesystem::directory_entry getSelected();
    virtual void up();
    virtual void down();
    virtual void pageUp();
    virtual void pageDown();
    virtual void select();
    virtual void setFilter(std::string filter);
    virtual void show();
    virtual void setDirectory(std::filesystem::path path, bool currentFolderOption=true);
    virtual void setDirectory(std::string path, bool currentFolderOption=true);
    virtual void clearEntries();
    virtual void draw(Vector3f at);

};

