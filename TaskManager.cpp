#include "TaskManager.h"


std::chrono::year_month_day TaskManager::toDate(std::string dateStr) {
     std::istringstream in{dateStr};
     std::chrono::year_month_day parsedDate;
     
     //basically the string should be made like year-month-day
     in >> std::chrono::parse("%F", parsedDate);

     if (!in.fail())
     {
        return parsedDate;
     } 
}