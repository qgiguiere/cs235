#include "MazeInterface.h"

class Maze: public MazeInterface
{
public:
	Maze(){};
    void setValue(int height, int width, int layer, int value);
    bool find_maze_path();
    std::string toString() const;
};