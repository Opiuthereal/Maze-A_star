#include <iostream>
#include <cstring>
#pragma once


class Maze {
	private : 
		int		_tab[21*12]; //Tableau pour les valeur
		const char*	_map[21*12]; //Tableau pour l'affichage "graphique" du maze
		int		_mapStat[21*12] = {0}; // Tableau pour le passage remplis automatiquement de 0
		const char*	_colorNum[10]; //couleurs pour afficher la heat map

		bool		estVide(int val);
		bool		estVideCoin(int val);
		bool		estRempliCoin(int val);

	public : 
				Maze(std::string maze_name);
		const char*	changeToTileset(int i); 
		int		getTab(int i);
		const char*	getMap(int i);
		int		getMapStat(int i);
		void		setTab(int i, int v);
		void		setMap(int i, const char* v);
		void		setMapStat(int i, int v);
		void		setPassage(int i);
		void		setColor(int i);

//Surcharge 
friend std::ostream& operator << (std::ostream& os, const Maze& m);
};
