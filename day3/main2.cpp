#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

    int result, ogr;
    std::vector<std::string> binaries;
    std::vector<int> posNotToCheck;
    std::string binary, ogrRate, epsilonRate;

    std::ifstream infile(argv[1]);
    
    while (infile >> binary)
    {
        binaries.push_back(binary);
    }

    std::vector<int> bitEnabledCount(binaries[0].length(), 0);
    std::vector<int> bitCount(binaries[0].length(), 0);

    for (int i = 0; i < binaries[0].length(); ++i)
    {
        for (int z = 0; z < binaries.size(); ++z)
        {
            if (std::find(posNotToCheck.begin(), posNotToCheck.end(), z) != posNotToCheck.end())
            {
                if (binaries[z].at(i) == '1')
                {
                    ++bitEnabledCount[i];
                }
                else
                {
                    posNotToCheck.push_back(z);
                }
                ++bitCount[i];
            }
        }
    }

    for (int i = 0; i < bitEnabledCount.size(); ++i)
    {
        if (bitEnabledCount[i] >= bitCount[i] / 2)
        {
            ogrRate += "1";
        }
        else
        {
            ogrRate += "0"; 
        }
    }

    std::cout << ogrRate << std::endl;

    return 0;
}
