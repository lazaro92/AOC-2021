#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct position {
    int x;
    int y;
};

std::vector<int> parseLine(const std::string &line, const char scape = ' ')
{
    std::vector<int> result;
    std::string strNum= "";

    for (const char &c : line)
    {
        if (c == scape && !strNum.empty())
        {
            result.push_back(std::stoi(strNum));
            strNum = "";
        }
        else
        {
            strNum += c;
        }
    }
    result.push_back(std::stoi(strNum));

    return result;
}

void markBoardPositionWhereNumberFound(
    const std::vector<std::vector<std::vector<int>>> &matrices,
    std::vector<std::vector<std::vector<bool>>> &boolMatrices,
    const int number
)
{
    // mark the boards position
    for (int i = 0; i < matrices.size(); ++i)
    {
        for (int x = 0; x < 5; ++x)
        {
            for (int y = 0; y < 5; ++y)
            {
                if (matrices[i][x][y] == number)
                {
                    boolMatrices[i][x][y] = true;
                }
            }
        }
    }
}

 bool getWinnerBoard(
    std::vector<std::vector<std::vector<int>>> &matrices,
    std::vector<std::vector<std::vector<bool>>> &boolMatrices,
    std::vector<std::vector<int>> &winner
)
{ 
    int sumHorizontal = 0;
    int sumVertical = 0;
    for (int i = 0; i < matrices.size(); ++i)
    {   
        for (int x = 0; x < 5; ++x)
        {
            for (int y = 0; y < 5; ++y)
            {
                if (boolMatrices[i][x][y] == true) ++sumHorizontal;
                if (boolMatrices[i][y][x] == true) ++sumVertical;
            }                
            if (sumHorizontal == 5 || sumVertical == 5)
            {
                winner = matrices[i];
                boolMatrices.erase(boolMatrices.begin() + i);
                matrices.erase(matrices.begin() + i);     
                return true;
            }
            sumHorizontal = 0;
            sumVertical = 0;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{ 
    if (argc == 0) return -1;

    // READING AND PREPARING THE DATA STRUCTURES

    std::string line;
    std::ifstream infile(argv[1]);

    std::vector<std::vector<std::vector<int>>> matrices;
    std::vector<int> numbers;

    if (std::getline(infile, line))
    {
        numbers = parseLine(line, ',');
        std::getline(infile, line); // get next empty line
    }

    int numMatrices= 0;
    std::vector<std::vector<int>> matrix;
    while (std::getline(infile, line))
    {
        if (line.length() == 0)
        {
            matrices.push_back(matrix);
            matrix.clear();
            ++numMatrices;
        }
        else
        {
            matrix.push_back(parseLine(line));
        }
    }
    matrices.push_back(matrix);

    // CREATING BOOL MATRICES n*5*5 -> FALSE
    std::vector<std::vector<std::vector<bool>>> boolMatrices;
    
    for (int i = 0; i < matrices.size(); ++i)
        boolMatrices.push_back(std::vector<std::vector<bool>> (5, std::vector<bool>(5)));

    // SOLVING THE PROBLEM
    bool temp, winner = false;
    int lastNum = 0, i = 0;
    std::vector<std::vector<int>> lastWinnerBoard;
    while (i < numbers.size())
    {
        // mark the boards position
        markBoardPositionWhereNumberFound(matrices, boolMatrices, numbers[i]);

        // check for the winner board
        temp = getWinnerBoard(matrices, boolMatrices, lastWinnerBoard);
        if (temp)
        {
            winner = temp;
            lastNum = i;
        }
        ++i;
    }
    
    i = lastNum + 1;

    int result = 0;
    if (winner) {
        std::cout << "A";
        for (const auto &row: lastWinnerBoard)
        {
            for (const auto &num: row)
            {
                if (std::find(numbers.begin(), numbers.begin() + i, num) == numbers.begin() + i)
                {
                    result += num;
                }                
            }
        }
        result *= numbers[i-1];
    }

    std::cout << std::to_string(result) << std::endl;

    return 0;
}
