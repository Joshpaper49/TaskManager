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

   //Attempt to read input
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
         std::vector<Task>& chosen_list = viewTasks(true);
         editTask(chosen_list);
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

std::vector<Task>& TaskManager::viewTasks(bool specificList) {
   //prints all of the task lists
   if(!specificList) {
      std::cout << "Current Tasks" << std::endl;
      std::cout << "============" << std::endl;
      printTaskList(currentTasks);

      std::cout << "Completed Tasks" << std::endl;
      std::cout << "============" << std::endl;
      printTaskList(completedTasks);

      std::cout << "Overdue Tasks" << std::endl;
      std::cout << "============" << std::endl;
      printTaskList(overdueTasks);

      return currentTasks;

   } 
   //takes in a choice, prints the list, and outputs a reference to the chosen task list
   else {
      std::cout << "[1] Current Tasks" << std::endl;
      std::cout << "[2] Completed Tasks" << std::endl;
      std::cout << "[3] Overdue Tasks" << std::endl;

      char input;

      while(true) {
         std::cout << "Enter your choice (1-3): ";

         if(!(std::cin >> input)) {
            std::cout << "Input unavailable. Exiting";
            return;
         } 
         
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');         
         
         if (input == '1' || input == '2' || input == '3') {
            break;
         }

         std::cout << "Invalid input. Try again" << std::endl;
      }

      switch(input) {
         case '1': {
            printTaskList(currentTasks);
            return currentTasks;
         }

         case '2': {
            printTaskList(completedTasks);
            return completedTasks;
         }

         case '3': {
            printTaskList(overdueTasks);
            return overdueTasks;
         }

      }
   }

}

void TaskManager::printTaskList(const std::vector<Task> &list) const {
   if (list.empty()) {
        std::cout << "No tasks to display.\n";
        return;
   }

   for(const auto &item: list) {
      std::cout << item << std::endl;
   }
}