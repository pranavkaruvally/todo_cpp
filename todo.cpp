#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Todo {
    private:
        fstream myfile;

         vector<string> vectorize()
        {
            vector<string> items;
            string myline;
            myfile.open("tasks.txt");

            if (myfile.is_open()) {
                while (myfile){
                    getline(myfile, myline);
                    items.push_back(myline);
                }
            }
            myfile.close();
            items.pop_back();

            return items;
        }

    public:
        void showEntireTasks()
        {
            vector<string> items = vectorize();
            int count = 1;

            for(string item: items) {
                cout<<count++<<") "<<item<<endl;
            }
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

        void pop()
        {
            vector<string> items = vectorize();
            myfile.open("tasks.txt", fstream::out | fstream::trunc);
            items.erase(items.begin());
            
            for (string item: items)
                myfile<<item<<'\n';

            myfile.close();
        }

        void clear()
        {
            myfile.open("tasks.txt", fstream::out | fstream::trunc);
            myfile << "";
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
    else if (strcmp(argv[1], "clear") == 0)
        tasks.clear();
    else if (strcmp(argv[1], "pop") == 0)
        tasks.pop();
    else
        return 1;   

    return 0;
}
