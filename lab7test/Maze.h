#ifndef MAZE_H
#define MAZE_H
#include <string>
#include "MazeInterface.h"
using namespace std;

class Maze: public MazeInterface {

    private:
        int height;
        int width;
        int numLayers;
        int*** maze;
        enum CellValue { OPEN, BLOCKED, PATH, EXIT, TEMPORARY };
        enum Directions {LEFT = 10, RIGHT = 11, UP = 12, DOWN = 13, OUT = 14, IN = 15};

    public:
    Maze(int height, int width, int numLayers);
    ~Maze();

    virtual void setValue(int height, int width, int layer, int value);

    bool find_maze_path(int height, int width, int z);

    virtual bool find_maze_path();

    virtual string toString() const;

};
#endif //MAZE_H