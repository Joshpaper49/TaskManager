#pragma once
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

class Task
{
    friend std::ostream &operator<<(std::ostream &os, const Task &rhs);

private:
    std::chrono::year_month_day dateCreated;
    std::chrono::year_month_day dateDue;
    std::string task_name = "Untitled";
    std::string description = "";
    bool completion_status = false;
    
    static std::vector<std::string> wrapText(const std::string &text, const size_t max_width);

public:
    Task(const std::chrono::year_month_day &dateDue, const std::string &task_name, const std::string &description);

    bool changeDueDate(const std::chrono::year_month_day &date);
    bool changeName(const std::string &name);
    void changeDescription(const std::string &description);
    void changeStatus();

    ~Task() = default;
};