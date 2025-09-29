#include <iostream>
#include<cstring>
#ifndef _labyrinth_h
#define _labyrinth_h


class Maze {
	private : 
		int		_tab[21*12]; //Tableau pour les valeur
		const char*	_map[21*12]; //Tableau pour l'affichage "graphique" du maze
		int		_mapStat[21*12]; // Tableau pour le passage
		/*int		_cols;
		int		_rows;*/
		const char*	changeToTileset(const char* map[21*12], int map2[21*12], int i); 
		bool		estVide(int val);
		bool		estVideCoin(int val);
		bool		estRempliCoin(int val);

	public : 
				Maze(std::string maze_name);
		int		getTab(int i);
		const char*	getMap(int i);
		int		getMapStat(int i);
		void		setTab(int i, int v);
		void		setMap(int i, const char* v);
		void		setMapStat(int i, int v);
		/*int	getCols();
		int	getRows();
		void	setCols(int v);
		void	setRows(int v);*/

//Surcharge 
friend std::ostream& operator << (std::ostream& os, const Maze& m);
};

#endif
