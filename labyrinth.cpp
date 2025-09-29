/////////////////////////////////////////////////////////////////
//     A FAIRE: Faire le passage dans le tableau mapStat       //
/////////////////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<cstring>
#include"labyrinth.h"
#include"agent.h"

using namespace std;

//Definition du constructeur
Maze::Maze(string maze_name) 
{
	const char* fleche_bas = "\xE2\xAC\x87"; // ⬇
	ifstream f(maze_name);
	for (int i=0; i<21*12; i++) 
	{
		f >> _tab[i];
	}
	f.close();
	for (int i=0; i<21*12; i++) 
	{
		if (estVide(_tab[i])) 
		{
			if (_tab[i] == 2) 
				_map[i] = fleche_bas;   // entrée
			else if (_tab[i] == 3) 
				_map[i] = fleche_bas; // sortie
			else 
				_map[i] = " ";  // case vide
		} 
		else
			_map[i] = changeToTileset(_map, _tab, i);
	}
}
	const char* Maze::changeToTileset(const char* map[21*12], int map2[21*12], int i)
{
    // Taille du labyrinth
    const int COLS = 21;
    const int ROWS = 12;

    // coordonnées de i
    int row = i / COLS;
    int col = i % COLS;

    // Récupère les voisins (avec vérification des limites)
    int haut   = (row > 0)        ? map2[i - COLS] : -1; 
    int bas    = (row < ROWS - 1) ? map2[i + COLS] : -1;
    int gauche = (col > 0)        ? map2[i - 1]    : -1;
    int droite = (col < COLS - 1) ? map2[i + 1]    : -1;
    //? est l'opérateur ternaire ici on as if (row > 0) {haut = map2[i-COLS]} else {haut = -1} 

    //Unicode
    const char* line     = "\xE2\x94\x80"; // ─
    const char* barre    = "\xE2\x94\x82"; // │
    const char* coin_hg  = "\xE2\x94\x8c"; // ┌
    const char* coin_hd  = "\xE2\x94\x90"; // ┐
    
    const char* coin_bg  = "\xE2\x94\x94"; // └
    const char* coin_bd  = "\xE2\x94\x98"; // ┘
    const char* barre_g  = "\xE2\x94\xA4"; // ┤
    
    const char* barre_d  = "\xE2\x94\x9c"; // ├
    const char* barre_b  = "\xE2\x94\xac"; // ┬
    
    const char* barre_h  = "\xE2\x94\xb4"; // ┴
    const char* plus     = "\xE2\x94\xbc"; // ┼
    const char* center	 = "\xC2\xB7"; // ·
    

    //coin de haut-gauche
    if (col == 0 && row == 0) 
	{
		if (estRempliCoin(droite) && estVideCoin(bas))
			return line;
		else if (estVideCoin(bas) && estRempliCoin(bas))
			return barre;
		else
			return coin_hg;

	}
	
	//coin de haut-droite
	else if (col == COLS-1 && row == 0) 
	{
                if (estRempliCoin(gauche) && estVideCoin(bas))
			return line;
                else if (estVideCoin(gauche) && estRempliCoin(bas))
                        return barre;
                else
                        return coin_hd;

	}
	
	//coin bas-gauche
	else if (col == 0 && row == ROWS-1) 
	{
                if (estRempliCoin(droite) && estVideCoin(haut))
                        return line;
                else if (estVideCoin(droite) && estRempliCoin(haut))
                        return barre;
                else
                        return coin_bg;

        }
	
	//coin de bas-droite
	else if (col == COLS-1 && row == ROWS-1) 
	{
                if (estRempliCoin(gauche) && estVideCoin(haut))
			return line;
                else if (estVideCoin(gauche) && estRempliCoin(haut))
                        return barre;
                else
                        return coin_bd;

        }
	//ligne haut
	else if (row == 0) 
	{
		if (estVideCoin(droite) && estVideCoin(gauche) && estRempliCoin(bas))
			return barre;
		else if (estVideCoin(gauche) && estRempliCoin(droite) && estRempliCoin(bas))
			return coin_hg;
		else if (estRempliCoin(gauche) && estVideCoin(droite) && estRempliCoin(bas))
			return coin_hd;
		else if (estRempliCoin(gauche) && estRempliCoin(droite) && estRempliCoin(bas))
			return barre_b;
		else
			return line;
	}

	//ligne bas
	else if (row == ROWS-1) 
        {
                if (estVide(droite) && estVide(gauche) && haut == 1)
                        return barre_h;
                else if (estVide(gauche) && droite == 1 && haut == 1)
                        return coin_bg;
                else if (gauche == 1 && estVide(droite) && haut == 1)
                        return coin_bd;
                else if (gauche == 1 && droite == 1 && haut == 1)
                	return barre_h;
                else
                        return line;
        }
        
        //ligne gauche
	else if (col == 0)
        {
                if (estVide(haut) && droite == 1 && bas == 1)
			return coin_hg;
		else if (haut == 1 && droite == 1 && estVide(bas))
			return coin_bg;
		else if (haut == 1 && estVide(droite) && estVide(bas))
			return barre_h;
		else if (estVide(haut) && estVide(droite) && bas == 1)
			return barre_b;
		else if (haut == 1 && droite == 1 && bas == 1)
			return barre_d;
                else
                        return barre;
        }
        
        //ligne de droite
	else if (col == COLS-1)
        {
                if (estVide(haut) && gauche == 1 && bas == 1)
                        return coin_hd;
                else if (haut == 1 && gauche == 1 && estVide(bas))
                        return coin_bd;
                else if (haut == 1 && estVide(gauche) && estVide(bas))
                        return barre_h; 
                else if (estVide(haut) && estVide(gauche) && bas == 1)
                        return barre_b;
                else if (haut == 1 && gauche == 1 && bas == 1)
                        return barre_g;
                else
                        return barre;
        }
        
        //au centre
	else 
	{
		if (haut == 1 && estVide(droite) && bas == 1 && estVide(gauche))
			return barre;
		else if (estVide(haut) && estVide(droite) &&  estVide(bas) && estVide(gauche))
			return center;
		else if (estVide(haut) && estVide(droite) &&  bas == 1 && estVide(gauche))
			return barre;
		else if (haut == 1 && estVide(droite) &&  estVide(bas) && estVide(gauche))
			return barre;
		else if (estVide(haut) && estVide(droite) &&  estVide(bas) && gauche == 1)
			return line;
		else if (estVide(haut) && droite == 1 && estVide(bas) && gauche == 1)
			return line;
		else if (estVide(haut) && droite == 1 &&  estVide(bas) && estVide(gauche))
			return line;
		else if (haut == 1 && droite == 1 && estVide(bas) && gauche == 1)
			return barre_h;
		else if (estVide(haut) && droite == 1 && bas == 1 && gauche == 1)
			return barre_b;
		else if (haut == 1 && droite == 1 && bas == 1 && estVide(gauche))
			return barre_d;
		else if(haut == 1 && estVide(droite) && bas == 1 && gauche == 1)
			return barre_g;
		else if (haut == 1 && droite == 1 && estVide(bas) && estVide(gauche))
			return coin_bg;
		else if (haut == 1 && estVide(droite) && estVide(bas) && gauche == 1)
			return coin_bd;
		else if (estVide(haut) && droite == 1 && bas == 1 && estVide(gauche))
			return coin_hg;
		else if (estVide(haut) && estVide(droite) && bas == 1 && gauche == 1)
			return coin_hd;
		else
			return plus;
		}
		
	//cas au cas-où qui ne sera jamais atteint
	return " ";
}

bool	Maze::estVide(int val)
{
	return val == 0 || val == 3 || val == 2;
}

bool	Maze::estVideCoin(int val)
{
	return val == 0;
}

bool	Maze::estRempliCoin(int val)
{
	return val == 1 || val == 2 || val == 3;
}

//Surcharge --> Affichage
ostream& operator<<(ostream& os, const Maze& l) {
	for (int i = 0; i < 21 * 12; ++i) {
		os << l._map[i];
		if ((i + 1) % 21 == 0)
			os << '\n';
	}
	return os;
}
// Getters et Setters
int		Maze::getTab(int i){return _tab[i];}
const char*	Maze::getMap(int i){return _map[i];}
int		Maze::getMapStat(int i){return _mapStat[i];}
void		Maze::setTab(int i, int v){_tab[i] = v;}
void		Maze::setMap(int i, const char* v) { _map[i] = v;}
void		Maze::setMapStat(int i, int v) {_mapStat[i] = v;}

/*
int	Maze::getCols()		{return _cols;}
int	Maze::getRows()		{return _rows;}
void	Maze::setCols(int v)	{_cols = v;}
void	Maze::setRows(int v)	{_rows = v;}
*/
int main() 
{
	Maze m("source.mz");
	Agent agent1(m);
	//agent1.setSud(3);
	//cout << agent1.getSud() << endl;
	cout << agent1;
	cout << m;
	return 0;
}
