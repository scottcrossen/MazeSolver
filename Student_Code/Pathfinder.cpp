#include "Pathfinder.h"
#include <istream>
#include <fstream>
#include <sstream>
#include <ctime>
Pathfinder::Pathfinder(void){
	xsize=5;
	ysize=5;
	zsize=5;
}
Pathfinder::Pathfinder(int xsize, int ysize, int zsize){
	this->xsize=xsize;
	this->ysize=ysize;
	this->zsize=zsize;
}
Pathfinder::~Pathfinder(void){}
string Pathfinder::getMaze(){
	return cached_maze.to_string();
}
void Pathfinder::createRandomMaze(){
	//srand(time(0));
	cached_maze.clear();
	for (int ziterator=0; ziterator<zsize;ziterator++)
		for (int yiterator=0; yiterator<ysize;yiterator++)
			for (int xiterator=0; xiterator<xsize; xiterator++)
				if (rand() % 2 == 1) cached_maze.poke(xiterator,yiterator,ziterator,false);
	cached_maze.poke(0,0,0,true);
	cached_maze.poke(xsize-1,ysize-1,zsize-1,true);
	return;
}
bool Pathfinder::importMaze(string file_name){
	ifstream map_in;
	map_in.open(file_name);
	string current_value;
	Maze current_maze = Maze(xsize, ysize, zsize);
	if (map_in.fail()) return false;
	for (int ziterator=0; ziterator<zsize;ziterator++){
		for (int yiterator=0; yiterator<ysize;yiterator++){
			getline(map_in,current_value);
			stringstream line_stream(current_value);
			for (int xiterator=0; xiterator<xsize; xiterator++){
				if ((line_stream >> current_value) && (current_value == "1" || current_value == "0")){
					if (current_value =="0") current_maze.poke(xiterator,yiterator,ziterator,false);
				}
				else return false;
			}
			if (!(line_stream >> current_value) && !(line_stream.fail())) return false;
		}
		getline(map_in,current_value);
		//if (ziterator != zsize - 1 && (current_value != string() || current_value != "\n")) return false;
	}
	if (!(map_in.eof()) || !current_maze.peek(0, 0, 0) || !current_maze.peek(xsize - 1, ysize - 1, zsize - 1)) return false;
	for (int ziterator = 0; ziterator<zsize; ziterator++)
	for (int yiterator = 0; yiterator<ysize; yiterator++)
	for (int xiterator = 0; xiterator<xsize; xiterator++)
		cached_maze.poke(xiterator, yiterator, ziterator, current_maze.peek(xiterator, yiterator, ziterator));
	return true;
}
vector<string> Pathfinder::next_pos(int xpos, int ypos, int zpos,Maze &current_maze){
	vector<string> current_vector;
	if (current_maze.peek(xpos,ypos,zpos)==false) return current_vector;
	current_maze.poke(xpos,ypos,zpos,false);
	if (xpos==xsize-1 && ypos==ysize-1 && zpos==zsize-1){
		current_vector.push_back("("+to_string(xpos)+", "+to_string(ypos)+", "+to_string(zpos)+")");
		return current_vector;
	}
	vector<string> next_vector;
	next_vector=next_pos(xpos+1, ypos, zpos, current_maze);
	if (next_vector.size()!=0){
		current_vector.push_back("("+to_string(xpos)+", "+to_string(ypos)+", "+to_string(zpos)+")");
		current_vector.insert( current_vector.end(), next_vector.begin(), next_vector.end() );
		return current_vector;
	}
	next_vector=next_pos(xpos, ypos+1, zpos, current_maze);
	if (next_vector.size()!=0){
		current_vector.push_back("("+to_string(xpos)+", "+to_string(ypos)+", "+to_string(zpos)+")");
		current_vector.insert( current_vector.end(), next_vector.begin(), next_vector.end() );
		return current_vector;
	}
	next_vector=next_pos(xpos, ypos, zpos+1, current_maze);
	if (next_vector.size()!=0){
		current_vector.push_back("("+to_string(xpos)+", "+to_string(ypos)+", "+to_string(zpos)+")");
		current_vector.insert( current_vector.end(), next_vector.begin(), next_vector.end() );
		return current_vector;
	}
	next_vector=next_pos(xpos-1, ypos, zpos, current_maze);
	if (next_vector.size()!=0){
		current_vector.push_back("("+to_string(xpos)+", "+to_string(ypos)+", "+to_string(zpos)+")");
		current_vector.insert( current_vector.end(), next_vector.begin(), next_vector.end() );
		return current_vector;
	}
	next_vector=next_pos(xpos, ypos-1, zpos, current_maze);
	if (next_vector.size()!=0){
		current_vector.push_back("("+to_string(xpos)+", "+to_string(ypos)+", "+to_string(zpos)+")");
		current_vector.insert( current_vector.end(), next_vector.begin(), next_vector.end() );
		return current_vector;
	}
	next_vector=next_pos(xpos, ypos, zpos-1, current_maze);
	if (next_vector.size()!=0){
		current_vector.push_back("("+to_string(xpos)+", "+to_string(ypos)+", "+to_string(zpos)+")");
		current_vector.insert( current_vector.end(), next_vector.begin(), next_vector.end() );
		return current_vector;
	}
	return current_vector;
}
vector<string> Pathfinder::solveMaze(){
	Maze current_maze=Maze(xsize,ysize,zsize);
	for (int ziterator=0; ziterator<zsize;ziterator++)
		for (int yiterator=0; yiterator<ysize;yiterator++)
			for (int xiterator=0; xiterator<xsize; xiterator++)
				current_maze.poke(xiterator,yiterator,ziterator,cached_maze.peek(xiterator,yiterator,ziterator));
	return Pathfinder::next_pos(0, 0, 0, current_maze);
}
