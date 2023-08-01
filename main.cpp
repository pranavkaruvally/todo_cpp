#include "todo.h"

void help(void);

int main(int argc, char **argv)
{
    if (argc < 2) {
       help();
       return 1;
    }

    Todo tasks;

    if (strcmp(argv[1], "showall") == 0)
        tasks.showEntireTasks();   
    else if (strcmp(argv[1], "show") == 0)
        tasks.show();
    else if (strcmp(argv[1], "push") == 0) {
        if (argc == 2) {
            string streamInput;
            getline(cin, streamInput);
            if (streamInput == "")
                return 1;
            tasks.push(streamInput);
        } else {
            string todoItem="";
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
        int pos = stoi(argv[2]);
        tasks.pop(pos);
    }
    else if (strcmp(argv[1], "insert") == 0) {
        string todoItem="";
        int pos = stoi(argv[2]);
        for (int i=3; i<argc; i++) {
            todoItem += argv[i];
            todoItem += " ";
        }
        todoItem.pop_back();
        tasks.insert(pos, todoItem);
    }
    else if (strcmp(argv[1], "insertfrom") == 0) {
        tasks.insertFrom(argv[2]);
    }
    else if (strcmp(argv[1], "swap") == 0) {
        int p1 = stoi(argv[2]);
        int p2 = stoi(argv[3]);
        tasks.swapTask(p1, p2);
    }
    else if (strcmp(argv[1], "help") == 0)
        help();
    else {
        help(); 
        return 1; 
    } 

    return 0;
}

void help(void) {
    cout << "todoc is to be used with following arguments\n\n";
    cout << "help: To display help\n";
    cout << "show: Shows the top priority task\n";
    cout << "showall: Shows all of the tasks\n";
    cout << "push: Add a new task to the bottom of the list\n";
    cout << "\tUsage: todoc push <item name>\n";
    cout << "pop: Delete the top priority task\n";
    cout << "insert: Insert a task to a specific position\n";
    cout << "\tUsage: todoc insert <position> <item name>\n";
    cout <<"delete: Delete a task from a specific position\n";
    cout << "\tUsage: todoc delete <position>\n";
    cout << "clear: To delete all tasks from the list\n";
    cout << "insertfrom: To insert tasks from a specific filename\n";
    cout << "\tUsage: todoc insertfrom <filename>\n";
    cout << "swap: To swap the priority of two tasks\n";
    cout << "\tUsage: todoc swap <position1> <position2>\n";
}