#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
                if (position <= 0 || position > items.size() + 1) {
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

        void insertFrom(string fileName) {
            string newline;
            fstream newFile(fileName);
            vector<string> newFileStrings;

            while (newFile) {
                getline(newFile, newline);
                newFileStrings.push_back(newline);
            }
            newFile.close();
            newFileStrings.pop_back();

            for (string task: newFileStrings) {
                this->push(task);
            }
        }

        void swapTask(int pos1, int pos2) {
            try {
                vector<string> items = vectorize();

                if (pos1 <= 0 || pos1 > items.size())
                    throw pos1;
                if (pos2 <= 0 || pos2 > items.size())
                    throw pos2;

                swap(items[pos1-1], items[pos2-1]);
                myfile.open("tasks.txt", fstream::out | fstream::trunc);
                
                for (int i=0; i<items.size(); i++)
                    myfile << items[i] <<'\n';

                myfile.close();
            } catch(int pos) {
                cout<<"Range Error: "<<pos<<" not within valid range\n";
            } catch(...) {
                cout << "The program encountered an error\n";
            }
        }
};