#pragma once
#include "PathfinderInterface.h"
#include "Maze.h"
#include <string>
class Pathfinder :
	public PathfinderInterface{
private:
	Maze cached_maze;
	int xsize;
	int ysize;
	int zsize;
	vector<string> next_pos(int xpos, int ypos, int zpos,Maze &current_maze);
public:
	Pathfinder(void);
	Pathfinder(int xsize, int ysize, int zsize);
	~Pathfinder(void);
	string getMaze();
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
};
