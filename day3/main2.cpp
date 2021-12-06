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

std::string getOGR(std::vector<std::string> binaries)
{
    std::string result;
    int ceros = 0, ones = 0;
    char pred;
    for (int i = 0; i < binaries[0].length(); ++i)
    {
        if (binaries.size() == 1) break;

        for (int z = 0; z < binaries.size(); ++z)
        {
            if (binaries[z].at(i) == '0')
                ++ceros;
            else
                ++ones;
        }

        pred = (ones >= ceros) ? '1': '0';

        for (int z = binaries.size()-1; z >= 0; --z)
        {
            if (binaries[z].at(i) != pred)
                binaries.erase(binaries.begin() + z); 
        }
        ceros = 0;
        ones = 0;
    }
    
    return binaries.at(0);
}

std::string getCSR(std::vector<std::string> binaries)
{
    std::string result;
    int ceros = 0, ones = 0;
    char pred;
    for (int i = 0; i < binaries[0].length(); ++i)
    {
        if (binaries.size() == 1) break;

        for (int z = 0; z < binaries.size(); ++z)
        {
            if (binaries[z].at(i) == '0')
                ++ceros;
            else
                ++ones;
        }

        pred = (ones >= ceros) ? '0': '1';

        for (int z = binaries.size()-1; z >= 0; --z)
        {
            if (binaries[z].at(i) != pred)
                binaries.erase(binaries.begin() + z); 
        }
        ceros = 0;
        ones = 0;
    }
    
    return binaries.at(0);
}


int main(int argc, char *argv[])
    { 
    if (argc == 0) return -1;

    int result, ogrNum, csrNum;
    std::vector<std::string> binaries;
    std::string binary, ogr, csr;

    std::ifstream infile(argv[1]);
    
    while (infile >> binary)
    {
        binaries.push_back(binary);
    }

    ogr = getOGR(binaries);
    csr = getCSR(binaries);

    ogrNum = binaryToDec(ogr);
    csrNum = binaryToDec(csr);

    std::cout << ogr << std::endl;    
    std::cout << csr << std::endl;    

    std::cout << "OGR: "<< std::to_string(ogrNum) << std::endl;    
    std::cout << "CSR: "<< std::to_string(csrNum) << std::endl;    
    std::cout << "Result: "<< std::to_string(ogrNum * csrNum) << std::endl;    

    return 0;
}
