#ifndef TASK_MANAGER_TASK_H
#define TASK_MANAGER_TASK_H

#include <iostream>
#include <string>


class Task{
private:
    int id{};
    bool done = false;
    std::string title;
    static bool IdValid(int);
    static bool TitleValid(const std::string&);

public:
    Task() = default;
    Task(int,bool,const std::string& );
    Task(int,const std::string&);
    [[nodiscard]] int getId()const;
    [[nodiscard]] const std::string & getTitle()const;
    [[nodiscard]] bool isDone()const;
    void SetTitle(const std::string&);
    void SetDone(bool);



};





















#endif //TASK_MANAGER_TASK_H
