#pragma once
#include <array>
#include <string>
using namespace std;
class Maze {
private:
	bool* map;
	int xsize;
	int ysize;
	int zsize;
public:
	Maze(void);
	Maze(int xsize,int ysize,int zsize);
	~Maze(void);
	bool poke(int xpos, int ypos, int zpos, bool value);
	bool peek(int xpos, int ypos, int zpos);
	void clear();
	string to_string();
};

