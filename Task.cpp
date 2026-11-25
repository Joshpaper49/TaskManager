#include "Task.h"

Task::Task(const std::chrono::year_month_day &dateDue, const std::string &task_name, const std::string &description, const std::chrono::year_month_day &dateCreated) : dateDue{dateDue}, task_name{task_name}, description{description}, dateCreated{dateCreated}
{
    if(!dateDue.ok()) {
        throw std::invalid_argument("Invalid due date.");
    }
}

std::ostream &operator<<(std::ostream &os, const Task &rhs)
{
    std::vector<std::string> line_filter = Task::wrapText(rhs.description, 40);

    //first line
    os << std::left << std::setw(15) << rhs.dateCreated << std::setw(15) << rhs.dateDue << std::setw(40) << line_filter.at(0) << std::setw(25) << rhs.task_name << std::boolalpha << rhs.completion_status << '\n';

    std::for_each(line_filter.begin()+1, line_filter.end(), [&os] (const std::string &line) {
        os << std::setw(24) << "" << std::left << std::setw(40) << line << '\n';
    });

    return os;
}

std::chrono::year_month_day Task::getCurrentLocalDate() {
    auto timepoint_now = std::chrono::system_clock::now();
    auto timepoint_local_now = std::chrono::current_zone()->to_local(timepoint_now);
    auto local_now = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(timepoint_local_now));

    return local_now;
};

std::vector<std::string> Task::wrapText(const std::string &text, const size_t max_width)
{
    std::vector<std::string> result;

    std::istringstream input_text{text};
    std::string word{};
    std::string currentLine{};

    while (input_text >> word)
    {

        size_t required_width = currentLine.size() + word.size();

        if (word.length() > max_width)
        {

            if (!currentLine.empty())
            {
                result.push_back(currentLine);
                currentLine.clear();
            }

            while (word.length() > max_width)
            {
                std::string temp{word.substr(0, max_width - 1) + "-"};
                result.push_back(temp);

                word.erase(0, max_width - 1);
            }

            currentLine = word;
        }
        else
        {
            if (!currentLine.empty())
            {
                required_width += 1;
            }

            if (required_width <= max_width)
            {
                if(!currentLine.empty()) {
                    currentLine += " " + word;
                } else {
                    currentLine += word;
                }
            } else {
                result.push_back(currentLine);
                currentLine = word;
            }
        }
    }

    if(!currentLine.empty())
        result.push_back(currentLine);
    if(result.empty())
        result.push_back("");

    return result;
}

bool Task::setDueDate(const std::chrono::year_month_day &date)
{
    if (!date.ok())
    {
        return false;
    }

    dateDue = date;
    return true;
}

bool Task::setName(const std::string &name)
{

    if (name.empty())
        return false;

    task_name = name;
    return true;
}

void Task::setDescription(const std::string &description)
{
    this->description = description;
}

void Task::setStatus()
{
    completion_status = !completion_status;
}

bool Task::isOverdue() {
    std::chrono::year_month_day current_date {getCurrentLocalDate()};
    return (current_date > dateDue); 
}