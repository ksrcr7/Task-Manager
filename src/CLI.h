

#ifndef TASK_MANAGER_CLI_H
#define TASK_MANAGER_CLI_H

#include "TaskManager.h"



class CLI {
public:
    [[maybe_unused]] static int run(TaskManager& , const std::vector<std::string>&);

};


#endif //TASK_MANAGER_CLI_H
