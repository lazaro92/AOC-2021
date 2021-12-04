#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc == 0) return -1;

    int num, sum, count = 0;
    std::vector<int> nums;    

    std::ifstream infile(argv[1]);

    while (infile >> num)
    {
        nums.push_back(num);
    }

    int maxN = 999999;
    for (int i=0; i < nums.size() - 2; ++i) {
        sum = nums[i] + nums[i+1] + nums[i+2];
        if (sum > maxN) {
            ++count;
        }
        maxN = sum;
    }
    
    std::cout << count << std::endl;

    return 0;
}
