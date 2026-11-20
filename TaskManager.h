#pragma once
#include "Task.h"
#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>


class TaskManager {
    private:
    std::vector<Task> currentTasks{};
    std::vector<Task> completedTasks{};
    std::vector<Task> overdueTasks{};

    static std::chrono::year_month_day toDate(std::string dateStr);
    void printTaskList(const std::vector<Task> &list) const;

    public:
    bool menu();
    std::vector<Task>& viewTasks(bool specificList = false);
    void loadTaskList();
    bool addTask();
    void editTask(std::vector<Task> &list);
    bool confirmExit();

    TaskManager() = default;

    ~TaskManager() = default;
};