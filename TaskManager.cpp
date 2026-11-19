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

bool TaskManager::menu() {
   bool isDone {false};

   std::cout << "Task Manager" << std::endl;
   std::cout << "============" << std::endl;
   std::cout << "L - Load Task List" << std::endl;
   std::cout << "V - View Tasks" << std::endl;
   std::cout << "A - Add Task" << std::endl;
   std::cout << "E - Edit Task" << std::endl;   
   std::cout << "X - Exit" << std::endl;

   std::string input;
   std::cout << "Enter your choice: ";
   std::getline(std::cin, input);

   //going to have to work on understanding this one
   if (!std::getline(std::cin, input)) {
      std::cout << "\nInput stream closed. Exiting.\n";
      isDone = true;
      return isDone;
   }

   if(input.size() != 1) {
      std::cout << "Error. Please enter a single letter.\n";
      return isDone;
   }

   char user_choice = static_cast<char>(std::toupper(static_cast<unsigned char>(input[0])));

   switch(user_choice) {
      case 'L': {
         loadTaskList();
         break;
      }
      case 'A': {
         addTask();
         break;
      }
      case 'V': {
         viewTasks();
         break;
      }
      case 'E': {
         //editTask();
         break;
      }
      case 'X': {
         isDone = confirmExit();
         break;
      }

      default: {
         std::cout << "Invalid input. Please try again!" << std::endl;
         break;
      }

   }


   return isDone;
}