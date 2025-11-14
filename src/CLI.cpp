#include "CLI.h"
#include "Task.h"
#include <iomanip>


namespace {

    int help(){
        std::cout
                << "Commands:\n"
                << "  add <title>    Add a new task\n"
                << "  list           List all tasks\n"
                << "  done <id>      Mark a task as done\n"
                << "  remove <id>    Remove a task\n"
                << "  help           Show this help\n";
        return 0;

    }

    std::string join_title(const std::vector<std::string>& args, std::size_t from){
        std::string result;
        for(std::size_t i = from; i<args.size();++i){
            if(!result.empty()){
                result += ' ';
            }
            result += args[i];
        }
        return result;
    }

    std::string decode_cli_escapes(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (std::size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (c == '\\' && i + 1 < s.size()) {
                char n = s[i + 1];
                if (n == 'n') { out += '\n'; ++i; continue; }
                if (n == 'r') { out += '\r'; ++i; continue; }
            }
            out += c;
        }
        return out;
    }













}

int CLI::run(TaskManager &tm, const std::vector<std::string> &args) {
    if(args.empty()){
        return help();
    }

    const std::string& cmd = args[0];

    if(cmd == "help"){
        return help();
    }

    else if(cmd == "add"){
        if(args.size() < 2){
            std::cerr<<"Title required\n";
            return 1;
        }
        std::string raw_title = join_title(args,1);
        std::string title = decode_cli_escapes(raw_title);

        try {
            int id = tm.add(title);
            std::cout << "Added task #" << id << "\n";
            return 0;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }
    else if(cmd == "list"){
        const auto& tasks = tm.list();

        if(tasks.empty()) {
            std::cout << "There are no tasks" << '\n';
            return 0;
        }
        for(const auto& it : tasks){
            if(it.isDone()){
                std::cout<<"[x] #"<<it.getId()<<" : "<<it.getTitle()<<'\n';
            }
            else{
                std::cout<<"[ ] #"<<it.getId()<<" : "<<it.getTitle()<<'\n';

            }
        }
        return 0;
    }





}


