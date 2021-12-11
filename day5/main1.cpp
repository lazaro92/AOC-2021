#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct position
{
    int x;
    int y;
};

void printIntMatrix(const std::vector<std::vector<int>> board)
{
    for (const auto &row: board)
    {
        for (const auto &col: row)
        {
            std::cout << std::to_string(col) << " ";
        }
        std::cout << std::endl;
    }
}

std::pair<int, int> parseFile(
        std::ifstream &infile,
        std::vector<std::pair<position, position>> &pairCoords
        )
{
    std::string line, strNum = "";
    char c;
    int num, i=0;    
    position pos1, pos2;    
    std::pair<int, int> boardSize;
    int maxX, maxY;

    while (std::getline(infile, line))
    {
        for (const auto &c: line)
        {
            if (c == ',')
            {
                if (i == 0)
                    pos1.x = std::stoi(strNum);
                else
                    pos2.x = std::stoi(strNum);
                strNum = "";
            }
            else if (c == ' ' && i == 0)
            {
                pos1.y = std::stoi(strNum);
                strNum = "";
                ++i; 
            } 
            else if (isdigit(c))
            {
                strNum += c;
            }
        }
        pos2.y = std::stoi(strNum);
        if (pos1.x == pos2.x || pos1.y == pos2.y) // only vertical or horitzontal lines
        {
            pairCoords.push_back(std::pair<position, position>(pos1, pos2));

            maxX = std::max(pos1.x, pos2.x);
            if (maxX > boardSize.first)
                boardSize.first = maxX; 
            
            maxY = std::max(pos1.y, pos2.y);
            if (maxY > boardSize.second)
                boardSize.second = maxY; 
        }

        i = 0;
        strNum = "";
    }
    boardSize.first += 1;
    boardSize.second += 1;

    return boardSize;
}

void processHVLines
(
    const std::vector<std::pair<position, position>> &vPairCoords,
    std::vector<std::vector<int>> &board
)
{
    for (const auto &line: vPairCoords)
    {
        if (line.first.x > line.second.x)
            for (int i = line.second.x; i <= line.first.x; ++i)
                ++board.at(i).at(line.first.y);
        else if (line.first.x < line.second.x)
            for (int i = line.first.x; i <= line.second.x; ++i)
                ++board.at(i).at(line.first.y);

        else if (line.first.y > line.second.y)
            for (int i = line.second.y; i <= line.first.y; ++i)
                ++board.at(line.first.x).at(i);
        else if (line.first.y < line.second.y)
            for (int i = line.first.y; i <= line.second.y; ++i)
                ++board.at(line.first.x).at(i);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 0) return -1;
    std::ifstream infile(argv[argc - 1]);

    std::vector<std::pair<position, position>> pairCoords;
    std::pair<int, int> boardSize = parseFile(infile, pairCoords);
    std::vector<std::vector<int>> board(boardSize.first, std::vector<int>(boardSize.second));

    processHVLines(pairCoords, board);

    int result = 0;
    for (const auto &row: board)
       for (const auto &value: row)
            if (value > 1)
                ++result;

    std::cout << "Result: " << std::to_string(result) << std::endl;

    return 0;
}
