#ifndef TASK_MANAGER_TASK_MANAGER_H
#define TASK_MANAGER_TASK_MANAGER_H

#include "Task.h"
#include <iostream>
#include <vector>
#include <string>




class TaskManager{
private:
    std::vector<Task> _tasks;
    int _next_id = 1;
    std::string storage_path;

public:
    explicit TaskManager(const std::string&);
    int add(const std::string &title);





};



























#endif //TASK_MANAGER_TASK_MANAGER_H
