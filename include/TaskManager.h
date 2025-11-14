#ifndef TASK_MANAGER_TASK_MANAGER_H
#define TASK_MANAGER_TASK_MANAGER_H

#include "Task.h"
#include <iostream>
#include <vector>
#include <string>
#include <optional>




class TaskManager{
private:
    std::vector<Task> _tasks;
    int _next_id = 1;
    std::string storage_path;
    std::optional<size_t> find_index_by_id(int);



public:
    explicit TaskManager(const std::string&);
    int add(const std::string &title);
    bool mark_done(int);
    bool remove(int);
    [[nodiscard]] bool save()const;
    bool load();
    [[nodiscard]] std::vector<Task> ShowTasks()const;






};



























#endif //TASK_MANAGER_TASK_MANAGER_H
