#pragma once
#include "Task.h"
#include <vector>
#include <chrono>
#include <string>
#include <sstream>


class TaskManager {
    private:
    std::vector<Task> currentTasks{};
    std::vector<Task> completedTasks{};
    std::vector<Task> overdueTasks{};

    static std::chrono::year_month_day toDate(std::string dateStr);

    public:
    void menu();
    void viewTasks();
    void loadTaskList();
    bool addTask();
    void editTask(Task &task);
    void exit();

    TaskManager() = default;

    ~TaskManager() = default;
};