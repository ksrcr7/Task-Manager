#include <iostream>
#include "TaskManager.h"
#include "CLI.h"

int main(int argc,char* argv[]) {

    TaskManager tm("data/tasks.txt");
    if (!tm.load()) {
        std::cerr << "Info: no tasks loaded (missing or empty file). Starting with an empty list.\n";
    }


    std::vector<std::string> args;
    args.reserve(argc > 1 ? argc - 1 : 0);
    for(int i = 1; i < argc ; ++i){
        args.emplace_back(argv[i]);
    }

    int rc = CLI::run(tm,args);
    if (!tm.save()) {
        std::cerr << "Warning: failed to save tasks.\n";
    }
    return rc;








}
