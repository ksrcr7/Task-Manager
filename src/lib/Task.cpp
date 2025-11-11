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

Task::Task(int n, const std::string &t) {
    if(!IdValid(n)){
        throw std::invalid_argument("Id must be >= 1.");
    }
    if(!TitleValid(t)){
        throw std::invalid_argument("Title must not be empty.");
    }

    id = n;
    title = t;


}

static std::string escape(const std::string& s){
    std::string out;
    out.reserve(s.size());

    for(unsigned char c : s){
        switch (c) {
            case '\\': out+="\\\\"; break;
            case ';': out+="\\;"; break;
            case '\n':out+="\\n"; break;
            case '\r': out+="\\r";break;
            default: out+= static_cast<char>(c);break;

        }
    }
    return out;
}

static std::string unescape(const std::string& s){
    std::string out;
    out.reserve(s.size());
    bool escape_mode = false;

    for(unsigned char c : s){
        if(!escape_mode){
            if(c == '\\'){
                escape_mode = true;
            }
            else{
                out += static_cast<char>(c);
            }
        }
        else{
            switch (c) {
                case '\\': out+="\\";break;
                case ';': out+=';';break;
                case 'n': out+='\n'; break;
                case 'r': out+='\r'; break;
                default:
                    out+='\\';
                    out+=static_cast<char>(c);
                    break;

            }
            escape_mode = false;
        }

    }
    if(escape_mode)out+='\\';
    return out;
}



