
#include "TaskManager.h"
#include <algorithm>
#include <stdexcept>
#include <cctype>


static bool stringValid(const std::string& message){
    if(message.empty())
        return false;
    if(std::all_of(message.begin(),message.end(),
                   [](unsigned char c){return isspace(c);}))
        return false;

    return true;
}


TaskManager::TaskManager(const std::string &st_path) {
    if(!stringValid(st_path)){
        throw std::invalid_argument("storage_path must not be empty.");
    }
    storage_path = st_path;

}

int TaskManager::add(const std::string &title) {
    int _id = _next_id;
    _tasks.emplace_back(_id,title);
    ++_next_id;
    return _id;
}

