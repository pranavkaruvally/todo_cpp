#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Todo {
    private:
        fstream myfile;

    public:
        void showEntireTasks()
        {
            string myline;
            int lineNum = 1;

            myfile.open("tasks.txt");

            if (myfile.is_open()) {
                while (myfile) {
                    getline(myfile, myline);
                    cout<< lineNum++ <<" "<<myline<<endl;
                }
            }

            myfile.close();
        }

        void show()
        {
            string myline;

            myfile.open("tasks.txt");

            if (myfile.is_open()) {
                getline(myfile, myline);
                cout<<myline<<endl;
            }

            myfile.close();
        }

        void push(string newItem)
        {
            myfile.open("tasks.txt", fstream::in | fstream::out | fstream::app);
            myfile << newItem << '\n';
            myfile.close();
        }
};

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
    else
        return 1;   

    return 0;
}
