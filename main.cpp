#include <iostream>
#include <vector>
#include "Task.h"
#include <chrono>


int main() {
    
    std::cout << "Hello ME" << std::endl;

    std::chrono::year_month_day test_date {std::chrono::year(2026), std::chrono::month(6), std::chrono::day(3)};

    std::vector <Task> test{};

    test.emplace_back(test_date);

    std::chrono::year_month_day new_due_date {std::chrono::year(2023), std::chrono::month(3), std::chrono::day(4)};

    test.at(0).changeDueDate(new_due_date);

    test.emplace_back(new_due_date, "My Stuff", "Implement getCurrentLocalDate to output local timezone current date then make sure it works as a default param for dateCreated that can be overrun has to use some toLocal method", test_date);

    test.at(0).changeName("Linux");
    test.at(0).changeStatus();


    for(auto &item: test) {
        std::cout << item << std::endl;
    }


    return 0;
}