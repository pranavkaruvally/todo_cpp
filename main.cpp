#include "todo.h"

int main(int argc, char **argv)
{
    if (argc < 2)
       return 1;

    Todo tasks;

    if (strcmp(argv[1], "showall") == 0)
        tasks.showEntireTasks();   
    else if (strcmp(argv[1], "show") == 0)
        tasks.show();
    else if (strcmp(argv[1], "push") == 0) {
        string todoItem="";
        for (int i=2; i<argc; i++) {
            todoItem += argv[i];
            todoItem += " ";
        }
        todoItem.pop_back();
        tasks.push(todoItem);
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
    else
        return 1;   

    return 0;
}