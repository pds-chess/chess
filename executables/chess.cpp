// src/main.cpp

#include <iostream>
#include "./view/consoleview.hpp" // Include our custom header

int main(int argc, std::string argv[]) {
    if(argc == 1 | argv[1] == "console")
        Console consoleview;
    return 0;
}
