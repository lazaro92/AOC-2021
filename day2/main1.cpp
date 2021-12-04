#include <fstream>
#include <iostream>
#include <string>

struct position {
    int x;
    int y;
};

int main(int argc, char *argv[])
    { 
    if (argc == 0) return -1;

    std::string instruction;
    int units;
    position pos;

    std::ifstream infile(argv[1]);
    
    while (infile >> instruction >> units)
    {
        if (instruction == "forward")
            pos.x += units;
        else if (instruction == "up")
            pos.y -= units;
        else if (instruction == "down")
            pos.y += units;
    }

    std::cout << "x: " << pos.x << " y: " << pos.y << std::endl; 
    std::cout << (pos.x * pos.y) << std::endl;

    return 0;
}
