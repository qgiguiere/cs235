#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <string>
#include <limits>
#include "Maze.h"
#include "MazeInterface.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please provide name of input and output files\n";
        return 1;
    }

    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input\n";
        return 1;
    }

    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {

        in.close();
        cerr << "Unable to open " << argv[2] << " for output\n";

    }

    int height;
    int width;
    int numLayers;
    in >> height >> width >> numLayers;
    in.ignore(std::numeric_limits<int>::max(), '\n');
    Maze* mazeObj = new Maze(height, width, numLayers);

    string line, command;
    for (size_t k = 0; k < (size_t) numLayers; ++k) {
        for (size_t i = 0; i < (size_t) height; ++i) {
            getline(in, line);
            if (line.empty()) {
                i--;
                continue;
            }
            istringstream ISS(line);
            int mazeValue;
            for (size_t j = 0; j < (size_t) width; ++j) {

                ISS >> mazeValue;
                mazeObj->setValue(i, j, k, mazeValue);
            }
        }
    }

    out << "Solve Maze: " << endl;
    out << mazeObj->toString() << endl;

    if (mazeObj->find_maze_path()) {

        out << "Solution:" << endl;
        out << mazeObj->toString();

    } else {

        out << "No Solution Exists!" << endl;

    }

    delete mazeObj;

    return 0;

}