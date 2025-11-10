#ifndef TASK_MANAGER_TASK_MANAGER_H
#define TASK_MANAGER_TASK_MANAGER_H

#include "Task.h"
#include <iostream>
#include <vector>
#include <string>




class TaskManager{
private:
    std::vector<Task> tasks;
    int next_id{};
    std::string storage_path;

public:
    explicit TaskManager(const std::string&);





};



























#endif //TASK_MANAGER_TASK_MANAGER_H
