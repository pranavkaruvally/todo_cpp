#include <iostream>
#include <vector>
#include <string>
#include <cstring>
// #include <fstream>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std:: cout << "BAD: EVENING\n";
        return 1;
    }
    if (strcmp(argv[1], "good") == 0) {
        if (argc == 2) {
            std::string someData;
            getline(std::cin, someData);
            std::cout << "GOOD: " << someData << std::endl;
        } else {
        std::cout << "GOOD: ";
        for (int i=3; i<argc; i++)
            std::cout << argv[i] << " ";
        std::cout << std::endl;
        }
    }

    return 0;
}