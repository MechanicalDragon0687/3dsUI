#pragma once
#include "Container.hpp"
#include "FileSelector.hpp"
#include <filesystem>
#include <string>

class FileEntry : public ContainerElement {
    protected:
        FileSelector* fs;
        std::filesystem::directory_entry entry;
    public:
    FileEntry(Vector3f location, Vector2f size, FileSelector* fs, std::string filter, std::string id="");
};