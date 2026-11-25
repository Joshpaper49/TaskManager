#include "TaskManager.h"

std::optional<std::chrono::year_month_day> TaskManager::toDate(std::string dateStr) {
     std::istringstream in{dateStr};
     std::chrono::year_month_day parsedDate;
     
     //basically the string should be made like year-month-day
     in >> std::chrono::parse("%F", parsedDate);

     if (!in.fail())
     {
        return parsedDate;
     } else {
      return std::nullopt;
     }
}

bool TaskManager::menu() {

   std::cout << std::endl;
   std::cout << "Task Manager" << std::endl;
   std::cout << "============" << std::endl;
   std::cout << "L - Load Task List" << std::endl;
   std::cout << "V - View Tasks" << std::endl;
   std::cout << "A - Add Task" << std::endl;
   std::cout << "E - Edit Task" << std::endl;   
   std::cout << "X - Exit" << std::endl;

   std::cout << std::endl;
   std::string input;
   std::cout << "Enter your choice: ";

   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   //Attempt to read input
   if (!std::getline(std::cin, input)) {
      std::cout << "\nInput stream closed. Exiting.\n";
      return true;
   }

   if(input.size() != 1) {
      std::cout << "Error. Please enter a single letter.\n";
      return false;
   }

   char user_choice = static_cast<char>(std::toupper(static_cast<unsigned char>(input[0])));

   switch(user_choice) {
      case 'L': {
         loadTaskList();
         break;
      }
      case 'A': {
         addTask(currentTasks);
         break;
      }
      case 'V': {
         viewTasks();
         break;
      }
      case 'E': {
         std::vector<Task>* chosen_list = selectList();
         if(chosen_list != nullptr) {
         editTask(*chosen_list);            
         }
         break;
      }
      case 'X': {
         return confirmExit();
      }

      default: {
         std::cout << "Invalid input. Please try again!" << std::endl;
         break;
      }

   }

   return false;
}

bool TaskManager::confirmExit() {
   std::cout << "Saving list and ending program." << std::endl;
   return true;
}

bool TaskManager::addTask(std::vector<Task> &list) {
   std::cout << std::endl;
   std::chrono::year_month_day parsedDueDate;

   //getting dutDate
   std::string year, month, day, raw_date;
   std::cout << "Initializing dueDate: " << std::endl;
   std::cout << "Enter year: ";
   std::cin >> year;
   std::cout << "Enter month: ";
   std::cin >> month;
   std::cout << "Enter day: ";
   std::cin >> day;
   
   raw_date = year + "-" + month + "-" + day;
   
   auto result = toDate(raw_date);
   if (!result.has_value()) {
    std::cout << "Unable to parse date.\n";
    return false;
   }

   //filtered date
   parsedDueDate = result.value();

   std::cin.ignore(
    std::numeric_limits<std::streamsize>::max(), '\n'
   );

   std::cout << std::endl;

   std::cout << "Enter task name: ";
   std::string task_name;
   std::getline(std::cin, task_name);

   std::cout << "Enter the task description: ";
   std::string description;
   std::getline(std::cin, description);

   try {
      list.emplace_back(parsedDueDate, task_name, description);
   } catch (const std::invalid_argument &e) {
      std::cout << e.what() << '\n';
      return false;
   }
   
   return true;
}

void TaskManager::editTask(std::vector<Task> &list)
{
   std::cout << "Edit task list is not implemented yet.\n";
}

void TaskManager::viewTasks() {
   //prints all of the task lists
      std::cout << std::endl;
      std::cout << "Current Tasks" << std::endl;
      std::cout << "============" << std::endl;
      printTaskList(currentTasks);

      std::cout << std::endl;
      std::cout << "Completed Tasks" << std::endl;
      std::cout << "============" << std::endl;
      printTaskList(completedTasks);

      std::cout << std::endl;
      std::cout << "Overdue Tasks" << std::endl;
      std::cout << "============" << std::endl;
      printTaskList(overdueTasks);
}

std::vector<Task>* TaskManager::selectList() {
      std::cout << "[1] Current Tasks" << std::endl;
      std::cout << "[2] Completed Tasks" << std::endl;
      std::cout << "[3] Overdue Tasks" << std::endl;

      char input;

      while(true) {
         std::cout << "Enter your choice (1-3): ";

         if(!(std::cin >> input)) {
            std::cout << "Input unavailable. Exiting";
            return nullptr;
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
            return &currentTasks;
         }

         case '2': {
            printTaskList(completedTasks);
            return &completedTasks;
         }

         case '3': {
            printTaskList(overdueTasks);
            return &overdueTasks;
         }

         default: {
            std::cout << "Invalid choice. Try again. \n";
            break;
         }

      }

      return nullptr;
}

void TaskManager::loadTaskList()
{
   std::cout << "Load task list is not implemented yet.\n";
}

void TaskManager::printTaskList(const std::vector<Task> &list) const {
   if (list.empty()) {
        std::cout << "No tasks to display.\n";
        return;
   }

   //header
   printHeader();

   for(const auto &item: list) {
      std::cout << item << std::endl;
   }
}

void TaskManager::printHeader() const {
       std::cout << std::left << std::setw(15) << "Date Created" << std::setw(15) << "Date Due" << std::setw(40) << "Description" << std::setw(25) << "Task Name" <<  "Completion Status" << '\n';
}