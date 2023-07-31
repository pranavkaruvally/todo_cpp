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
        ~Todo()
        {
            if (myfile.is_open())
                myfile.close();
        }

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

        void pop(int position=1)
        {
            vector<string> items = vectorize();

            try {
                if (position < 1 || position > items.size()) {
                    throw position;
                }

                myfile.open("tasks.txt", fstream::out | fstream::trunc);
                items.erase(items.begin() + (position - 1));
                
                for (string item: items)
                    myfile<<item<<'\n';

                myfile.close();
            } catch(int pos) {
                cout<<"Insertion Error: "<<pos<<" not within valid range\n";
            } catch(...) {
                cout<<"The program encountered an error\n";
            }
        }

        void clear()
        {
            myfile.open("tasks.txt", fstream::out | fstream::trunc);
            myfile << "";
            myfile.close();
        }

        void insert(int position, string newItem)
        {
            vector<string> items = vectorize();

            try {
                if (position < 0 || position > items.size() + 1) {
                    //We place items.size() + 1 so we can use insert for appending as well
                    throw position;
                }

                myfile.open("tasks.txt", fstream::out | fstream::trunc);
                items.insert(items.begin() + (position - 1), newItem);

                for (string item: items)
                    myfile << item << '\n';

                myfile.close();
            } catch(int pos) {
                cout<<"Insertion Error: "<<pos<<" not within valid range\n";
            } catch(...) {
                cout<<"The program encountered an error\n";
            }
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
