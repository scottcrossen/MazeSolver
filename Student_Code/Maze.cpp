#include "Maze.h"
#include <sstream>
using namespace std;
Maze::Maze(void)
{
	xsize=5;
	ysize=5;
	zsize=5;
	map=new bool[xsize*ysize*zsize];
	for (int iterator=0; iterator <= xsize*ysize*zsize-1; iterator++) map[iterator]=true;
}
Maze::Maze(int xsize,int ysize,int zsize)
{
	this->xsize=xsize;
	this->ysize=ysize;
	this->zsize=zsize;
	map=new bool[xsize*ysize*zsize];
	for (int iterator=0; iterator <= xsize*ysize*zsize-1; iterator++) map[iterator]=true;
}
Maze::~Maze(void){
	delete map;
}
bool Maze::poke(int xpos, int ypos, int zpos, bool value){
	if ((xpos < xsize) && (ypos < ysize) && (zpos < zsize) && (xpos >= 0) && (ypos >= 0) && (zpos >= 0)){
		map[xpos+ypos*xsize+zpos*xsize*ysize]=value;
		return true;
	}
	return false;
}
bool Maze::peek(int xpos, int ypos, int zpos){
	if ((xpos < xsize) && (ypos < ysize) && (zpos < zsize) && (xpos >= 0) && (ypos >= 0) && (zpos >= 0)){
		return map[xpos+ypos*xsize+zpos*xsize*ysize];
	}
	return false;
}
void Maze::clear(){
	for (int iterator=0; iterator <= xsize*ysize*zsize-1; iterator++) map[iterator]=true;
}
string Maze::to_string(){
	stringstream output;
	for (int ziterator=0; ziterator<zsize;ziterator++){
		for (int yiterator=0; yiterator<ysize;yiterator++){
			for (int xiterator=0; xiterator<xsize; xiterator++){
				if (map[xiterator+yiterator*xsize+ziterator*xsize*ysize]== true) output << "1";
				else output << "0";
				if (xiterator<xsize-1) output << " ";
			}
			if (ziterator<zsize-1 || yiterator<ysize-1) output << "\n";
		}
		if (ziterator<zsize-1) output << "\n";
	}
	return output.str();
}