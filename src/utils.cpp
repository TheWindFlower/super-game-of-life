#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include "../include/utils.hpp"

using std::tuple;
using std::vector;

std::vector<std::tuple<int, int, bool, int>> next_generation(const vector<tuple<int, int, bool, int>> &current_status, int rows, int columns)
{

    vector<tuple<int, int, bool, int>> next_status;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int alive_neighbors = 0;
            // Check neighbors
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int neighbor_row = i + x;
                    int neighbor_column = j + y;
                    // Check if neighbor is within bounds
                    if (neighbor_row >= 0 && neighbor_row < rows && neighbor_column >= 0 && neighbor_column < columns)
                    {
                        // Ignore current cell
                        if (x == 0 && y == 0)
                        {
                            continue;
                        }
                        // Count alive neighbors
                        if (std::get<2>(current_status[neighbor_row * columns + neighbor_column]))
                        {
                            alive_neighbors++;
                        }
                    }
                }
            }

            // Apply Game of Life rules
            bool current_cell_status = std::get<2>(current_status[i * columns + j]);
            if (current_cell_status && alive_neighbors < 2)
            {
                // Underpopulation
                // check if the celle is a super cells
                if (std::get<3>(current_status[i, j]))
                {
                    next_status.emplace_back(i, j, true, false);
                }
                else
                {
                    next_status.emplace_back(i, j, false, false);
                }
            }
            else if (current_cell_status && (alive_neighbors == 2 || alive_neighbors == 3))
            { // Survival
                if (std::get<3>(current_status[i, j]))
                {
                    next_status.emplace_back(i, j, true, true);
                }
                else
                {
                    next_status.emplace_back(i, j, true, false);
                }
            }
            else if (current_cell_status && alive_neighbors > 3)
            { // Overpopulation
                if (std::get<3>(current_status[i, j]))
                {
                    next_status.emplace_back(i, j, true, false);
                }
                else
                {
                    next_status.emplace_back(i, j, false, false);
                }
            }
            else if (!current_cell_status && alive_neighbors == 3)
            { // Reproduction
                next_status.emplace_back(i, j, true, false);
            }
            else
            { // Stasis
                if (std::get<3>(current_status[i, j]) && current_cell_status)
                {
                    next_status.emplace_back(i, j, current_cell_status, true);
                }
                else
                {
                    next_status.emplace_back(i, j, current_cell_status, false);
                }
            }
        }
    }
    return (next_status);
}
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
