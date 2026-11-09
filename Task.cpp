#include "Task.h"


    Task::Task(const std::chrono::year_month_day &dateDue, const std::string &task_name, const std::string &description) : dateCreated{std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())}, dateDue{dateDue}, task_name{task_name}, description{description}            

    // should make this a helper function in taskmanger to filter parse the user input before passing it into the task. The task shouldn't have to do it
    {
       /* std::istringstream in{dueDateStr};
        std::chrono::year_month_day parsedDate;

        in >> std::chrono::parse("%F", parsedDate);

        if (!in.fail())
        {
            dateDue = parsedDate;
        } */
    }



std::ostream& operator<<(std::ostream &os, const Task &rhs) {
   /*  return os << rhs.dateCreated << "   " << rhs.dateDue << "   " << rhs.description <<
    "   " << rhs.task_name << "  " << std::boolalpha << rhs.completion_status << std::endl; */

    return os << std::left << std::setw(12) << rhs.dateCreated <<
    std::setw(12) << rhs.dateDue << std::setw(40) << rhs.description << rhs.task_name << std::boolalpha << std::right << std::setw(6) <<
    rhs.completion_status;
}

std::vector<std::string> Task::wrapText(const std::string &text, const size_t max_width) {
    std::vector<std::string> result;

    std::istringstream input_text{text};
    std::string word{};

    std::string currentLine{};

    while(input_text >> word) {
        
        size_t required_width = currentLine.size() + word.size();

        if(!currentLine.empty()) {
            required_width += 1;
        }

        if(required_width <= max_width) {
            currentLine += " " + word;
        } else {
            result.push_back(currentLine);
            currentLine = word;
        }
    }

    result.push_back(currentLine);

    return result;
}

bool Task::changeDueDate(const std::chrono::year_month_day &date) {
    if(!date.ok()) {
        return false;
    }

    dateDue = date;
    return true;
}

bool Task::changeName(const std::string &name) {

    if(name.empty())
        return false;

    task_name = name;
    return true;
}

void Task::changeDescription(const std::string &description) {
    this->description = description;
}

void Task::changeStatus() {
    completion_status = !completion_status;
} 