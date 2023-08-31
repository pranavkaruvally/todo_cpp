//#include "todo.h"
#include "todo_port.h"
#include <cstring>

void help(void);

int main(int argc, char **argv)
{
    if (argc < 2) {
       help();
       return 1;
    }

    sql::Driver *driver = sql::mariadb::get_driver_instance();
    sql::SQLString url("jdbc:mariadb://localhost:3306/todoc");
    sql::Properties properties({{"user", "pranav"}, {"password", "navaneeth"}});
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));


    Todo tasks {conn};

    if (strcmp(argv[1], "showall") == 0)
        tasks.showEntireTasks();   
    /*
    else if (strcmp(argv[1], "show") == 0)
        tasks.show();
    else if (strcmp(argv[1], "push") == 0) {
        if (argc == 2) {
            std::string streamInput;
            getline(std::cin, streamInput);
            if (streamInput == "")
                return 1;
            tasks.push(streamInput);
        } else {
            std::string todoItem="";
            for (int i=2; i<argc; i++) {
                todoItem += argv[i];
                todoItem += " ";
            }
            todoItem.pop_back();
            tasks.push(todoItem);
        }
    }
    else if (strcmp(argv[1], "clear") == 0)
        tasks.clear();
    else if (strcmp(argv[1], "pop") == 0)
        tasks.pop();
    else if (strcmp(argv[1], "delete") == 0) {
        int pos = std::stoi(argv[2]);
        tasks.pop(pos);
    }
    else if (strcmp(argv[1], "insert") == 0) {
        int pos = std::stoi(argv[2]);
        if (argc == 3) {
            std::string streamInput;
            getline(std::cin, streamInput);
            if (streamInput == "")
                return 1;
            tasks.insert(pos, streamInput);
        }
        else {
            std::string todoItem="";
            for (int i=3; i<argc; i++) {
                todoItem += argv[i];
                todoItem += " ";
            }
            todoItem.pop_back();
            tasks.insert(pos, todoItem);
        }
    }
    else if (strcmp(argv[1], "insertfrom") == 0) {
        tasks.insertFrom(argv[2]);
    }
    else if (strcmp(argv[1], "swap") == 0) {
        int p1 = std::stoi(argv[2]);
        int p2 = std::stoi(argv[3]);
        tasks.swapTask(p1, p2);
    }*/
    else if (strcmp(argv[1], "help") == 0)
        help();
    else {
        help(); 
        return 1; 
    }

    return 0;
}

void help(void) {
    std::cout << "todoc is to be used with following arguments\n\n";
    std::cout << "help: To display help\n";
    std::cout << "show: Shows the top priority task\n";
    std::cout << "showall: Shows all of the tasks\n";
    std::cout << "push: Add a new task to the bottom of the list\n";
    std::cout << "\tUsage: todoc push <item name>\n";
    std::cout << "pop: Delete the top priority task\n";
    std::cout << "insert: Insert a task to a specific position\n";
    std::cout << "\tUsage: todoc insert <position> <item name>\n";
    std::cout <<"delete: Delete a task from a specific position\n";
    std::cout << "\tUsage: todoc delete <position>\n";
    std::cout << "clear: To delete all tasks from the list\n";
    std::cout << "insertfrom: To insert tasks from a specific filename\n";
    std::cout << "\tUsage: todoc insertfrom <filename>\n";
    std::cout << "swap: To swap the priority of two tasks\n";
    std::cout << "\tUsage: todoc swap <position1> <position2>\n";
}
