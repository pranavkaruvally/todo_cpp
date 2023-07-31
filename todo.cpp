#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

class Todo {
    ifstream myfile;

    public:
        Todo()
        {
            myfile.open("tasks.txt");
        }

        void showEntireTasks()
        {
            string myline;
            int lineNum = 1;

            if (myfile.is_open()) {
                while (myfile) {
                    getline(myfile, myline);
                    cout<< lineNum++ <<" "<<myline<<endl;
                }
            }
        }

        void show()
        {
            string myline;

            if (myfile.is_open()) {
                getline(myfile, myline);
                cout<<myline<<endl;
            }
        }
};

int main(int argc, char **argv)
{
    if (argc != 2)
       return 1;

    Todo tasks;

    if (strcmp(argv[1],"showall") == 0)
        tasks.showEntireTasks();   
    else if (strcmp(argv[1], "show") == 0)
        tasks.show();
    else
        return 1;   

    return 0;
}
