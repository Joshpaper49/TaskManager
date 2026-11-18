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
    std::chrono::year_month_day dateDue;
    std::string task_name = "Untitled";
    std::string description = "";
    std::chrono::year_month_day dateCreated;    
    bool completion_status = false;
    
    static std::vector<std::string> wrapText(const std::string &text, const size_t max_width);
    static std::chrono::year_month_day getCurrentLocalDate();

public:
    Task(const std::chrono::year_month_day &dateDue, const std::string &task_name = "Untitled", const std::string &description = "", const std::chrono::year_month_day &dateCreated = getCurrentLocalDate());

    bool changeDueDate(const std::chrono::year_month_day &date);
    bool changeName(const std::string &name);
    void changeDescription(const std::string &description);
    void changeStatus();
    bool isOverdue();

    ~Task() = default;
};