#include <iostream>
#include <vector>
#include "Task.h"
#include <chrono>


int main() {
    
    std::cout << "Hello ME" << std::endl;

    std::chrono::year_month_day test_date {std::chrono::year(2026), std::chrono::month(6), std::chrono::day(3)};

    std::vector <Task> test{};

    test.emplace_back(test_date, "Computer", "I have to create my own PC in two days");

    std::cout << test.at(0) << std::endl;

    std::chrono::year_month_day new_due_date {std::chrono::year(2023), std::chrono::month(3), std::chrono::day(4)};

    test.at(0).changeDueDate(new_due_date);

    std::cout << test.at(0) << std::endl;

    test.at(0).changeName("Linux");
    test.at(0).changeDescription("My ROMI stuff is going well!");
    test.at(0).changeStatus();

    std::cout << test.at(0) << std::endl;


    return 0;
}