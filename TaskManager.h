#pragma once
#include "Task.h"
#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
#include <optional>
#include <limits>


class TaskManager {
    private:
    std::vector<Task> currentTasks{};
    std::vector<Task> completedTasks{};
    std::vector<Task> overdueTasks{};

    static std::optional<std::chrono::year_month_day> toDate(std::string dateStr);
    void printTaskList(const std::vector<Task> &list) const;
    void printHeader() const;


    public:
    bool menu();
    void viewTasks();
    std::vector<Task>* selectList();    
    void loadTaskList();
    bool addTask(std::vector<Task> &list);
    void editTask(std::vector<Task> &list);
    bool confirmExit();

    TaskManager() = default;

    ~TaskManager() = default;
};