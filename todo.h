#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

class Todo {
    private:
        std::fstream myfile;

         std::vector<std::string> vectorize()
        {
            std::vector<std::string> items;
            std::string myline;
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
            std::vector<std::string> items = vectorize();
            int count = 1;

            for(std::string item: items) {
                std::cout<<count++<<") "<<item<<'\n';
            }
        }

        void show()
        {
            std::string myline;

            myfile.open("tasks.txt");

            if (myfile.is_open()) {
                getline(myfile, myline);
                std::cout<<myline<<'\n';
            }

            myfile.close();
        }

        void push(std::string newItem)
        {
            myfile.open("tasks.txt", std::fstream::in | std::fstream::out | std::fstream::app);
            myfile << newItem << '\n';
            myfile.close();
        }

        void pop(int position=1)
        {
            std::vector<std::string> items = vectorize();

            try {
                if (position < 1 || position > static_cast<int>(items.size())) {
                    throw position;
                }

                myfile.open("tasks.txt", std::fstream::out | std::fstream::trunc);
                items.erase(items.begin() + (position - 1));
                
                for (std::string item: items)
                    myfile<<item<<'\n';

                myfile.close();
            } catch(int pos) {
                std::cout<<"Insertion Error: "<<pos<<" not within valid range\n";
            } catch(...) {
                std::cout<<"The program encountered an error\n";
            }
        }

        void clear()
        {
            myfile.open("tasks.txt", std::fstream::out | std::fstream::trunc);
            myfile << "";
            myfile.close();
        }

        void insert(int position, std::string newItem)
        {
            std::vector<std::string> items = vectorize();

            try {
                if (position <= 0 || position > static_cast<int>(items.size()) + 1) {
                    //We place items.size() + 1 so we can use insert for appending as well
                    throw position;
                }

                myfile.open("tasks.txt", std::fstream::out | std::fstream::trunc);
                items.insert(items.begin() + (position - 1), newItem);

                for (std::string item: items)
                    myfile << item << '\n';

                myfile.close();
            } catch(int pos) {
                std::cout<<"Insertion Error: "<<pos<<" not within valid range\n";
            } catch(...) {
                std::cout<<"The program encountered an error\n";
            }
        }

        void insertFrom(std::string fileName) {
            std::string newline;
            std::fstream newFile(fileName);
            std::vector<std::string> newFileStrings;

            while (newFile) {
                getline(newFile, newline);
                newFileStrings.push_back(newline);
            }
            newFile.close();
            newFileStrings.pop_back();

            for (std::string task: newFileStrings) {
                this->push(task);
            }
        }

        void swapTask(int pos1, int pos2) {
            try {
                std::vector<std::string> items = vectorize();
                int itemsize = static_cast<int>(items.size());
                if (pos1 <= 0 || pos1 > itemsize)
                    throw pos1;
                if (pos2 <= 0 || pos2 > itemsize)
                    throw pos2;

                swap(items[pos1-1], items[pos2-1]);
                myfile.open("tasks.txt", std::fstream::out | std::fstream::trunc);
                
                for (int i=0; i<itemsize; i++)
                    myfile << items[i] <<'\n';

                myfile.close();
            } catch(int pos) {
                std::cout<<"Range Error: "<<pos<<" not within valid range\n";
            } catch(...) {
                std::cout << "The program encountered an error\n";
            }
        }
};