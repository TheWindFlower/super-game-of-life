#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

using std::tuple;
using std::vector;

vector<tuple<int, int, bool, int>> start(std::string filename, int rows, int columns)
{
    vector<tuple<int, int, bool, int>> coordinates;

    // Initialize all coordinates to false (0) and not special
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            coordinates.push_back(std::make_tuple(i, j, false, 0));
        }
    }

    // Open file and set bool to true (1) for specified coordinates and set
    std::ifstream inputFile(filename);
    int x, y, kind;
    while (inputFile >> x >> y >> kind)
    {
        std::cout << kind << std::endl;
        int index = x * columns + y;
        coordinates[index] = std::make_tuple(x, y, true, kind);
    }
    inputFile.close();

    ////debug
    std::ofstream outputFile("debug");
    for (const auto &coord : coordinates)
    {
        outputFile << std::get<0>(coord) << " " << std::get<1>(coord) << " "
                   << std::get<2>(coord) << " " << std::get<3>(coord) << "\n";
    }
    outputFile.close();
    ////
    return coordinates;
}

void grid_gen(int x, int y)
{
    std::srand(time(NULL)); // seed the random number generator

    vector<std::string> end;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if ((double)std::rand() / RAND_MAX < 0.5)
            {
                if ((double)std::rand() / RAND_MAX < 0.5)
                {
                    end.push_back(std::to_string(i) + " " + std::to_string(j) + " " + std::to_string(1));
                }
                else
                {
                    end.push_back(std::to_string(i) + " " + std::to_string(j) + " " + std::to_string(0));
                }
            }
        }
    }

    std::ofstream file("data/board.brd");
    file.clear(); // clear the file
    for (const std::string &cell : end)
    {
        file << cell << std::endl;
    }
    file.close();
}
int main()
{
    int x = 2;
    int y = 2;
    grid_gen(x, y);
    start("data/board.brd", x, y);
}