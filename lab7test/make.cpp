#include "Maze.h"
#include <sstream>
#include <ostream>


Maze::Maze(int height, int width, int numLayers) {
    this->height = height;
    this->width = width;
    this->numLayers = numLayers;
    this->maze = new int** [this->height];
    for (size_t i = 0; i < (size_t) this->height; ++i) {
        this->maze[i] = new int* [this->width];
        for (size_t j = 0; j < (size_t) this->width; ++j) {
            this->maze[i][j] = new int[this->numLayers];
        }
    }
}

Maze::~Maze() {
    for (size_t i = 0; i < (size_t) this->height; ++i) {
        for (size_t j = 0; j < (size_t) this->width; ++j) {
            delete [] this->maze[i][j];
        }
        delete [] this->maze[i];
    }
    delete [] this->maze;
}

void Maze::setValue(int height, int width, int layer, int value) {
    this->maze[height][width][layer] = value;
}

/** Check for solution and mark path */
bool Maze::find_maze_path(int height, int width, int layer) {
    /** Check if outside of maze */
    if (height < 0 || width < 0 || layer < 0 || height >= this->height || width >= this->width || layer >= this->numLayers) {
        return false;
    }
    /** If is invalid path */
    if (this->maze[height][width][layer] != OPEN) {
        return false;
    } /** If is end of Maze */
    else if (height == (this->height - 1) && width == (this->width - 1) && layer == (this->numLayers - 1)) {
        this->maze[height][width][layer] = EXIT;
        return true;
    }
    /** Mark coordinates on path */
    this->maze[height][width][layer] = PATH;
    if (find_maze_path(height, width - 1, layer)) {
        this->maze[height][width][layer] = LEFT;
        return true;
    }
    else if (find_maze_path(height, width + 1, layer)) {
        this->maze[height][width][layer] = RIGHT;
        return true;
    }
    else if (find_maze_path(height - 1, width, layer)) {
        this->maze[height][width][layer] = UP;
        return true;
    }
    else if (find_maze_path(height + 1, width, layer)) {
        this->maze[height][width][layer] = DOWN;
        return true;
    }
    else if (find_maze_path(height, width, layer - 1)) {
        this->maze[height][width][layer] = OUT;
        return true;
    }
    else if (find_maze_path(height, width, layer + 1)) {
        this->maze[height][width][layer] = IN;
        return true;
    }
    this->maze[height][width][layer] = TEMPORARY;
    return false;
}

/** Wrapper function */
bool Maze::find_maze_path() {
    return find_maze_path(0, 0, 0);
}

/** Output maze path */
string Maze::toString() const {
    ostringstream os;
    string returnString;
    for (size_t k = 0; k < (size_t) this->numLayers; ++k) {
        os << "Layer " << k + 1 << endl;
        for (size_t i = 0; i < (size_t) this->height; ++i) {
            os << " ";
            for (int j = 0; j < this->width; ++j) {
                int currentCell = this->maze[i][j][k];
                if (currentCell == PATH) {
                    os << (j != (this->width - 1) ? "2 " : "2");
                }
                else if (currentCell == BLOCKED) {
                    os << (j != (this->width - 1) ? "X " : "X");
                }
                else if (currentCell == OPEN || currentCell == TEMPORARY) {
                    os << (j != (this->width - 1) ? "_ " : "_");
                }
                else if (currentCell == EXIT) {
                    os << (j != (this->width - 1) ? "E " : "E");
                }
                if (currentCell == LEFT) {
                    os << (j != (this->width - 1) ? "L " : "L");
                } 
                else if (currentCell == RIGHT) {
                    os << (j != (this->width - 1) ? "R " : "R");
                } 
                else if (currentCell == UP) {
                    os << (j != (this->width - 1) ? "U " : "U");
                } 
                else if (currentCell == DOWN) {
                    os << (j != (this->width - 1) ? "D " : "D");
                } 
                else if (currentCell == OUT) {
                    os << (j != (this->width - 1) ? "O " : "O");
                } 
                else if (currentCell == IN) {
                    os << (j != (this->width - 1) ? "I " : "I");
                }
            }
            os << endl;
        }
    }
    returnString = os.str();
    return returnString;

}