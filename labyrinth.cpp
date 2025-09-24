#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<iterator>

using namespace std;

class Maze {
	private : 
		int _tab[21*12]; //Tableau pour les valeur
		const char* _map[21*12]; //Tableau pour l'affichage "graffique" du maze

		const char* changeToTileset(const char* map[21*12], int map2[21*12], int i); //méthode pour bien afficher le main
		bool	estVide(int val);
		bool	estVideCoin(int val);
		bool	estRempliCoin(int val);

	public : 
		//Constructor : affichage du maze
		Maze(string maze_name);

//Surcharge 
friend std::ostream& operator << (std::ostream& os, const Maze& m);
};

//-------------------------------------------------------------------------

//Definition des constructeurs
Maze::Maze(string maze_name) {
ifstream f(maze_name);
    for (int i=0; i<21*12; i++) {
        f >> _tab[i];
    }
    f.close();

    for (int i=0; i<21*12; i++) {
        if (estVide(_tab[i])) {
            if (_tab[i] == 2) _map[i] = "E";   // entrée
            else if (_tab[i] == 3) _map[i] = "S"; // sortie
            else _map[i] = " ";  // case vide
        } else {
            _map[i] = changeToTileset(_map, _tab, i); // mur avec joli caractère
        }
    }
}
	const char* Maze::changeToTileset(const char* map[21*12], int map2[21*12], int i)
{
    // Taille de la grille
    const int COLS = 21;
    const int ROWS = 12;

    // Calcule les coordonnées (ligne, colonne)
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
    const char* barre_g  = "\xE2\x94\xa4"; // ┤
    
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
/////////////////////////////////////////////////////////////////////
	//ligne haut
	else if (row == 0) 
	{
		if (estVideCoin(droite) && estVideCoin(gauche) && estRempliCoin(bas))
			return barre;
		else if (estVideCoin(gauche) && estRempliCoin(droite) && estRempliCoin(bas))
			return coin_hg;
		else if (estRempliCoin(gauche) && estVideCoin(droite) && estRempliCoin(bas))
			return coin_hd;
		else
			return line;
	}
/////////////////////////////////////////////////////////////////////
	//ligne bas
	else if (row == ROWS-1) 
        {
                if (estVide(droite) && estVide(gauche) && haut == 1)
                        return barre_h;
                else if (estVide(gauche) && droite == 1 && haut == 1)
                        return coin_bg;
                else if (gauche == 1 && estVide(droite) && haut == 1)
                        return coin_bd;
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
		else if (estVide(haut) && droite == 1 && estVide(bas) && gauche == 1)
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
		else if (haut == 1 && estVide(droite) && bas == 1 && gauche == 1)
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

int main() 
{
	Maze m("source.mz");
	cout << m;
	return 0;
}
