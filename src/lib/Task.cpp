#include "Task.h"
#include <algorithm>

bool Task::IdValid(int s) {
    if(s < 1)return false;
    return true;
}

bool Task::TitleValid(const std::string & t) {
    if(t.empty())return false;
    else if(std::all_of(t.begin(),t.end(),
                        [](unsigned char c){return std::isspace(c);}))
        return false;

    return true;
}

int Task::getId() const {
    return id;
}

const std::string &Task::getTitle() const {
    return title;
}

bool Task::isDone() const {
    return done;
}

Task::Task(int n, bool d, const std::string& t) {
    if(!IdValid(n)){
        throw std::invalid_argument("Id must be >= 1.");
    }
    if(!TitleValid(t)){
        throw std::invalid_argument("Title must not be empty.");
    }

    id = n;
    done = d;
    title = t;




}

void Task::SetTitle(const std::string &t) {
    if(!TitleValid(t)){
        throw std::invalid_argument("Title must not be empty.");
    }
    title = t;
}

void Task::SetDone(bool d) {
    done = d;

}



