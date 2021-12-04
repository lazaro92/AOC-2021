#include <fstream>
#include <iostream>
#include <string>

struct position {
    int x = 0;
    int y = 0;
    int aim = 0;
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
        {
            pos.y += pos.aim * units;
            pos.x += units;
        }
        else if (instruction == "up")
        {
            pos.aim -= units;
        }
        else if (instruction == "down")
        {
            pos.aim += units;
        }
    }

    std::cout << std::to_string(pos.x * pos.y) << std::endl;

    return 0;
}
