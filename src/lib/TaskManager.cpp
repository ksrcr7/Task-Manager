
#include "TaskManager.h"
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <fstream>

static bool split_three_fields(const std::string& line,std::string& f1,
                               std::string& f2,std::string& f3){

    std::string cur;
    int seps = 0;
    bool esc = false;

    for(unsigned char ch : line){
        if(esc){cur += static_cast<char>(ch);esc = false; continue;}
        if(ch == '\\'){esc = true; cur += '\\'; continue;}
        if(ch == ';' && seps < 2){
            if(seps == 0)f1 = cur;
            else f2 = cur;
            cur.clear();
            ++seps;
        } else{
            cur += static_cast<char>(ch);
        }
    }
    if(seps == 2){
        f3 = cur;
        return true;
    }
    return false;

}

static inline void chomp_cr(std::string& s){
    if(!s.empty() && s.back() == '\r')
        s.pop_back();
}

static inline std::string trim(const std::string& s){
    size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
    while(e > b && std::isspace(static_cast<unsigned char>(s[e-1]))) --e;
    return s.substr(b,e-b);
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

std::optional<size_t> TaskManager::find_index_by_id(int s) {
    if(s < 1)return std::nullopt;
    for(size_t i = 0; i < _tasks.size(); ++i){
        if(_tasks[i].getId() == s)
            return i;
    }
    return std::nullopt;
}

bool TaskManager::mark_done(int id) {
    auto idx = find_index_by_id(id);
    if(!idx.has_value())
        return false;

    _tasks[*idx].SetDone(true);
    return true;
}

bool TaskManager::remove (int id) {
    auto idx = find_index_by_id(id);
    if(!idx.has_value())
        return false;

    _tasks.erase(_tasks.begin() + *idx);
    return true;
}

bool TaskManager::save() const {
    std::ofstream fout(storage_path,std::ios::trunc);
    if(!fout.is_open())return false;

    for(const auto& it : _tasks){
        const int id = it.getId();
        const int done_flag = it.isDone()? 1:0;
        const std::string title_escaped = escape(it.getTitle());

        fout<< id <<";"<<done_flag<<";"<<title_escaped<<'\n';
        if(!fout)return false;
    }
    return true;
}

bool TaskManager::load() {
    std::ifstream fin(storage_path);
    if(!fin.is_open())
        return false;

    _tasks.clear();
    int max_id = 0;
    std::string line;
    int loaded = 0;

    while (std::getline(fin,line)){
        chomp_cr(line);
        if(line.empty())continue;

        std::string f1,f2,f3;
        if(!split_three_fields(line,f1,f2,f3))continue;

        f1 = trim(f1);
        f2 = trim(f2);

        int id = 0;
        try {
            id = std::stoi(f1);
            
        } catch (...) {
            continue;
        }
        if(id < 1)continue;

        int done_flag = -1;
        if(f2 == "0")done_flag = 0;
        else if(f2 == "1")done_flag = 1;
        else continue;

        const std::string title = unescape(f3);
        try {
            _tasks.emplace_back(id,done_flag == 1,title);
        } catch (...) {
            continue;
        }

        max_id = std::max(max_id,id);
        ++loaded;
    }

    _next_id = (loaded > 0)? (max_id + 1):1;
    return loaded > 0;


}

std::vector<Task> TaskManager::list() const {
    return _tasks;
}





