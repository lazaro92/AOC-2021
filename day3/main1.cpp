#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int binaryToDec(std::string &binary)
{
    int index = 1, result = 0;

    for (int i=binary.length() - 1; i >= 0; --i)
    {
        if (binary.at(i) == '1')
        {
            result += index;
        }
        index *= 2;
    }
    
    return result;
}

int main(int argc, char *argv[])
    { 
    if (argc == 0) return -1;

    int result, gammaDec, epsilonDec;
    std::vector<std::string> binaries;
    std::string binary, gammaRate, epsilonRate;

    std::ifstream infile(argv[1]);
    
    while (infile >> binary)
    {
        binaries.push_back(binary);
    }

    std::vector<int> bitCount (binaries[0].length(), 0);

    for (auto &element: binaries)
    {
        for (int i=0; i < element.length(); i++)
        {
            if (element.at(i) == '1')
            {
                ++bitCount[i];
            }
        }    
    }

    for (auto &num: bitCount)
    {
        if (num >= binaries.size() / 2)
        {
            gammaRate += "1";
            epsilonRate += "0";
        }
        else
        {
            gammaRate += "0"; 
            epsilonRate += "1"; 
        }
    }

    gammaDec = binaryToDec(gammaRate);
    epsilonDec = binaryToDec(epsilonRate);
    result = gammaDec * epsilonDec;

    std::cout << std::to_string(gammaDec) << std::endl;
    std::cout << std::to_string(epsilonDec) << std::endl;
    std::cout << std::to_string(result) << std::endl;

    return 0;
}
