#include <filesystem>
#include <regex>
#include <locale>
#include <string>
#include "gui/gui.hpp"

bool sortMenuSelections(std::filesystem::directory_entry a, std::filesystem::directory_entry b) {
    if (a.is_directory() == b.is_directory()){
        std::string apath = a.path().filename().generic_string();
        std::string bpath = b.path().filename().generic_string();
        toLower(apath);
        toLower(bpath);
        return apath < bpath;
    }
    return a.is_directory();
}
bool FileSelector::canSelectFolder(std::vector<std::filesystem::directory_entry>* dirEntries) {
    return this->selectFolder && std::count_if(dirEntries->begin(),dirEntries->end(),[](std::filesystem::directory_entry e){return !e.is_directory();}) > 0;
}

FileSelector::FileSelector(Vector3f location, Vector2f size, std::string id, std::string label, uint32_t flags, std::string filter, bool canSelectFolder) : Panel(location,size,id,label,flags) {
    this->selected=false;
    this->selectFolder=canSelectFolder; 
    this->setFilter(filter);
    this->registerListener({KeyDown,[this](eventData data){
        if (data.key & KEY_UP)
            this->up();
        else if (data.key & KEY_DOWN)
            this->down();
        else if (data.key & KEY_RIGHT)
            this->pageDown();
        else if (data.key & KEY_LEFT)
            this->pageUp();
        else if (data.key & KEY_A)
            this->select();
        else if (data.key & KEY_B)
            this->setDirectory(this->cwd.parent_path());
        else if (data.key & KEY_START)
            return false;
        return true;
    }
    });
    this->registerListener({Close,[this](eventData data){
        this->selected=true;
        this->hide();
        return true;
    }});
}
std::filesystem::directory_entry FileSelector::getSelected() {
    return std::any_cast<std::filesystem::directory_entry>((*this->selection)->getData());
}
void FileSelector::up() {
    if (this->selection==this->entries.begin()) {
        this->selection=this->entries.end()-1;
        if (this->entries.size() <= ENTRIES_PER_SCREEN)
            this->top = this->entries.begin();
        else
            this->top = this->entries.end()-(ENTRIES_PER_SCREEN);
    }else{
        if (this->selection == this->top) {
            this->top--;
        }
        this->selection--;
    }
    this->markDirty();
}
void FileSelector::down() {
    if (this->selection==this->entries.end()-1) {
        this->selection=this->entries.begin();
            this->top = this->entries.begin();
    }else{
        if (this->selection == this->top+(ENTRIES_PER_SCREEN-1)) {
            this->top++;
        }
        this->selection++;
    }
    this->markDirty();
}
void FileSelector::pageUp() {
    if (this->top-ENTRIES_PER_SCREEN <= this->entries.begin()) {
        this->top=this->entries.begin();
    }else{
        this->top-=ENTRIES_PER_SCREEN;
    }
    if (this->selection-ENTRIES_PER_SCREEN <= this->entries.begin()) {
        this->selection=this->entries.begin();
    }else{
        this->selection-=ENTRIES_PER_SCREEN;
    }
    this->markDirty();

}
void FileSelector::pageDown() {
    if (this->top+ENTRIES_PER_SCREEN >= this->entries.end()) {
        this->selection=this->entries.end()-1;
        if (this->entries.size() <= ENTRIES_PER_SCREEN)
            this->top = this->entries.begin();
        else
            this->top = this->entries.end()-(ENTRIES_PER_SCREEN);
    }else{
        this->top+=ENTRIES_PER_SCREEN;
        this->selection+=ENTRIES_PER_SCREEN;
    }
    this->markDirty();

}
void FileSelector::select() {
    std::filesystem::directory_entry entry = std::any_cast<std::filesystem::directory_entry>((*this->selection)->getData());
    if (entry.path().compare(this->cwd)!=0 && entry.is_directory()) {
        this->setDirectory(entry.path());
    }else{
        this->event({Close});
    }
}
void FileSelector::setFilter(std::string filter) {
    this->filter = std::regex(".+\\."+filter);
    this->setDirectory(this->cwd,this->selectFolder);
}
void FileSelector::show() {
    if (this->entries.size() < 1) {
        this->setDirectory(std::filesystem::path("/"),this->selectFolder);
    }
    this->selection=this->entries.begin();
    this->top=this->entries.begin();
    Panel::show();

}
void FileSelector::setDirectory(std::filesystem::path path, bool currentFolderOption) {
    this->clearEntries();
    std::vector<std::filesystem::directory_entry> dirEntries;
    //TODO: not hardcode height
    Vector2f entrySize = {
        this->size.x - (PANEL_BORDER*2) - PANEL_MARGIN*2 - PANEL_PADDING_LEFT - PANEL_PADDING_RIGHT,
        40
    };
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::string filename = entry.path().filename();
        if (filename[0]=='.' || (!entry.is_directory() && !std::regex_match(filename,this->filter)))
            continue;
        
        dirEntries.push_back(entry);
    }
    std::sort(dirEntries.begin(), dirEntries.end(), sortMenuSelections);
    
    if ( currentFolderOption && canSelectFolder(&dirEntries)) {
        this->entries.push_back(new ListEntry(entrySize,0.67,"<Select Folder>",std::filesystem::directory_entry(path),this->id+".ListEntryCurrent"));
    }
    
    if (path.has_parent_path() && path.parent_path().compare(path)) {
        this->entries.push_back(new ListEntry(entrySize,0.67,"..",std::filesystem::directory_entry(path.parent_path()),this->id+".ListEntryParent"));
    }
    // TODO: not hardcode scale
    for (std::filesystem::directory_entry e : dirEntries) {
        this->entries.push_back(
            new ListEntry(entrySize,0.67,e.path().filename().generic_string(), std::filesystem::directory_entry(e),this->id+"."+e.path().filename().generic_string())
        );
    }
    this->top = this->entries.begin();
    this->selection = this->entries.begin();
    this->cwd = path;
    this->markDirty();
}
void FileSelector::setDirectory(std::string path, bool currentFolderOption) {
    this->setDirectory(std::filesystem::path(path),currentFolderOption);
}
void FileSelector::clearEntries() {
    for (ListEntry* e : this->entries)
        delete e;
    this->entries.clear();
}
void FileSelector::draw(Vector3f at) {
    Panel::draw(at);
        at = at+(this->getLocationAbsolute()+Vector3f{PANEL_PADDING_LEFT+PANEL_MARGIN+PANEL_BORDER,PANEL_PADDING_TOP+PANEL_MARGIN+PANEL_BORDER,0});
    int cnt = 0;
    for (std::vector<ListEntry*>::iterator cur = top; cur != this->entries.end() && cnt <  ENTRIES_PER_SCREEN; cur++) {
        (*cur)->draw(at+Vector3f{0,40.0f*cnt,0},cur==this->selection);
        cnt++;
    }
}

