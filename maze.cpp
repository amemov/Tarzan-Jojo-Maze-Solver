// Project 3 - Tarzan and Jojo Maze Solver
// Anton Shepelev for Analysis of Algorithms COT4400
// Problem: in given maze Tarzan has to get to Jojo and he can move from cell to cell ( 3-4 cells need to be passed ) Moves in direction designated by a cell
// Input: txt file desribed as “Tarzan and Jojo” maze problem (from “MAD MAZES: Intriguing Mind Twisters for Puzzle Buffs, Game Nutsand Other Smart People” by Robert Abbott).
// Output: sequence of steps to get final state Jojo ( e.g.: S-3, E-4, etc )
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void backTracking(int i, int j, std::vector<std::string>& solution, std::string** adjMatrix, int& r, int& c);
void writeOutput(std::vector<std::string>& solution);

int main() {

    // Read txt file with maze
    std::ifstream maze("input.txt");
    if (!maze.is_open()) {
        std::cout << "Can't open the file! Make sure it is in the same directory!\n";
        return 0;
    }

    // Read parameteres of maze: rows,columns, and startitng position
    int R, C, i, j; std::string temp; std::vector <std::string> solution{};
    maze >> R;
    maze >> C;
    maze >> i;
    maze >> j;

    // Initialize 2D pointer arrray of strings - adjMatrix 
    std::string** adjMatrix = new std::string * [R];
    for (int i = 0; i < R; i++) {
        adjMatrix[i] = new std::string[C];
    }

    // Fill out adjMatrix with information from txt file
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            maze >> temp;
            adjMatrix[i][j] = temp;
        }
    }
    // Close file
    maze.close();

    // Normalize values ( in order to pass by ref w/o problems )
    int rows = R - 1; int cols = C - 1;

    backTracking(i - 1, j - 1, solution, adjMatrix, rows, cols);

    return 0;
}
// Recursive search of correct path in depth-first order. Takes i,j - starting position, solution vector, adjMatrix, and size of maze ( rows , columns )
void backTracking(int i, int j, std::vector<std::string>& solution, std::string** adjMatrix, int& r, int& c) {

    // Base case: Found Jojo
    if (adjMatrix[i][j] == "J")
        writeOutput(solution);

    // Make 2 copies of solution for each recursive call
    std::vector<std::string> path3 = solution;
    std::vector<std::string> path4 = solution;

    // Is cell explored?
    if (adjMatrix[i][j] != "O") {

        // Check which direction to explore. Check if can go move by 3 and/or by 4
        // Add to temporary vector current vertex with selected number of steps and call backTracking.
        // Copy way. Mark cell.
        std::string way = adjMatrix[i][j]; std::string temp;
        adjMatrix[i][j] = "O";
        /* Regular Ways*/
        if (way == "S") {
            if (i + 3 <= r) {
                if (adjMatrix[i + 3][j] != "X") {
                    temp = way;
                    temp.append("-3");
                    path3.push_back(temp);
                    backTracking(i + 3, j, path3, adjMatrix, r, c);
                }
            }
            if (i + 4 <= r) {
                if (adjMatrix[i + 4][j] != "X") {
                    temp = way;
                    temp.append("-4");
                    path4.push_back(temp);
                    backTracking(i + 4, j, path4, adjMatrix, r, c);
                }
            }
        }
        else if (way == "N") {
            if (i - 3 >= 0) {
                if (adjMatrix[i - 3][j] != "X") {
                    temp = way;
                    temp.append("-3");
                    path3.push_back(temp);
                    backTracking(i - 3, j, path3, adjMatrix, r, c);
                }
            }
            if (i - 4 >= 0) {
                if (adjMatrix[i - 4][j] != "X") {
                    temp = way;
                    temp.append("-4");
                    path4.push_back(temp);
                    backTracking(i - 4, j, path4, adjMatrix, r, c);
                }
            }
        }
        else if (way == "W") {
            if (j - 3 >= 0) {
                if (adjMatrix[i][j - 3] != "X") {
                    temp = way;
                    temp.append("-3");
                    path3.push_back(temp);
                    backTracking(i, j - 3, path3, adjMatrix, r, c);
                }
            }
            if (j - 4 >= 0) {
                if (adjMatrix[i][j - 4] != "X") {
                    temp = way;
                    temp.append("-4");
                    path4.push_back(temp);
                    backTracking(i, j - 4, path4, adjMatrix, r, c);
                }
            }
        }
        else if (way == "E") {
            if (j + 3 <= c) {
                if (adjMatrix[i][j + 3] != "X") {
                    temp = way;
                    temp.append("-3");
                    path3.push_back(temp);
                    backTracking(i, j + 3, path3, adjMatrix, r, c);
                }
            }
            if (j + 4 <= c) {
                if (adjMatrix[i][j + 4] != "X") {
                    temp = way;
                    temp.append("-4");
                    path4.push_back(temp);
                    backTracking(i, j + 4, path4, adjMatrix, r, c);
                }
            }
        }
        /* Spicy Ways */
        else if (way == "NW") {
            if (i - 3 >= 0 && j - 3 >= 0) {
                if (adjMatrix[i - 3][j - 3] != "X") {
                    temp = way;
                    temp.append("-3");
                    path3.push_back(temp);
                    backTracking(i - 3, j - 3, path3, adjMatrix, r, c);
                }
            }
            if (i - 4 >= 0 && j - 4 >= 0) {
                if (adjMatrix[i - 4][j - 4] != "X") {
                    temp = way;
                    temp.append("-4");
                    path4.push_back(temp);
                    backTracking(i - 4, j - 4, path4, adjMatrix, r, c);
                }
            }
        }
        else if (way == "NE") {
            if (i - 3 >= 0 && j + 3 <= c) {
                if (adjMatrix[i - 3][j + 3] != "X") {
                    temp = way;
                    temp.append("-3");
                    path3.push_back(temp);
                    backTracking(i - 3, j + 3, path3, adjMatrix, r, c);
                }
            }
            if (i - 4 >= 0 && j + 4 <= c) {
                if (adjMatrix[i - 4][j + 4] != "X") {
                    temp = way;
                    temp.append("-4");
                    path4.push_back(temp);
                    backTracking(i - 4, j + 4, path4, adjMatrix, r, c);
                }
            }
        }
        else if (way == "SE") {
        if (i + 3 <= r && j + 3 <= c) {
            if (adjMatrix[i + 3][j + 3] != "X") {
                temp = way;
                temp.append("-3");
                path3.push_back(temp);
                backTracking(i + 3, j + 3, path3, adjMatrix, r, c);
            }
        }
        if (i + 4 <= r && j + 4 <= c) {
            if (adjMatrix[i + 4][j + 4] != "X") {
                temp = way;
                temp.append("-4");
                path4.push_back(temp);
                backTracking(i + 4, j + 4, path4, adjMatrix, r, c);
            }
        }
        }
        else if (way == "SW") {
            if (i + 3 <= r && j - 3 >= 0) {
                if (adjMatrix[i + 3][j - 3] != "X") {
                    temp = way;
                    temp.append("-3");
                    path3.push_back(temp);
                    backTracking(i + 3, j - 3, path3, adjMatrix, r, c);
                }
            }
            if (i + 4 <= r && j - 4 >= 0) {
                if (adjMatrix[i + 4][j - 4] != "X") {
                    temp = way;
                    temp.append("-4");
                    path4.push_back(temp);
                    backTracking(i + 4, j - 4, path4, adjMatrix, r, c);
                }
            }
        }
        
    }
    
}
// Writes solution vector into 'output.txt'
void writeOutput(std::vector<std::string>& solution) {
    // Open file
    std::ofstream out;
    out.open("output.txt");
    
    // Read vector: perform write
    for (auto way : solution)
        out << way << " ";

    // Close file
    out.close();
}