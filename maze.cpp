#include<iostream>
#include<fstream>
#include<cstring>
#include"maze.h"

using namespace std;

//Definition du constructeur
Maze::Maze(string maze_name) 
{
	//const char* fleche_bas = "\xE2\xAC\x87"; // ⬇
	ifstream f(maze_name);
	for (int i=0; i<21*12; i++) 
	{
		f >> _tab[i];
	}
	f.close();
}

// Getters et Setters
int		Maze::getTab(int i) const		{ return _tab[i]; }
/*const char*	Maze::getMap(int i)			{ return _map[i]; }
int		Maze::getMapStat(int i)			{ return _mapStat[i]; }
void		Maze::setTab(int i, int v)		{ _tab[i] = v; }
void		Maze::setMap(int i, const char* v)	{ _map[i] = v; }
void		Maze::setMapStat(int i, int v)		{ _mapStat[i] = v; }*/

