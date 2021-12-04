#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    int n1, n2, count = 0;
    
    if (argc == 0) return -1;

    std::ifstream infile(argv[1]);

    infile >> n1;
    
    while (infile >> n2)
    {
        if (n2 > n1)
        {
            ++count;
        }
        n1 = n2;
    }
    std::cout << count << std::endl;    

    return 0;
}
