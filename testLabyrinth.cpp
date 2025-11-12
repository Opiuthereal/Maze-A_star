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

    // Exemple de logique simple :
    // mur = 1, vide = 0 
    bool h = (haut   == 1);
    bool b = (bas    == 1);
    bool g = (gauche == 1);
    bool d = (droite == 1);

    // Cas coin
    if (h && g && !b && !d) return coin_bd; // ┘
    if (h && d && !b && !g) return coin_bg; // └
    if (b && g && !h && !d) return coin_hd; // ┐
    if (b && d && !h && !g) return coin_hg; // ┌

    // Cas barres
    if ((h && b) && !g && !d) return barre;   // │
    if ((g && d) && !h && !b) return line;    // ─

    // Cas intersections
    if (h && b && g && d)  return plus;        // ┼
    if (h && b && d)       return barre_g;    // ┤
    if (h && b && g)       return barre_d;    // ├
    if (g && d && h)       return barre_h;    // ┴
    if (g && d && b)       return barre_b;    // ┬

    // Sinon, mur simple horizontal
    return line;
}

bool	Maze::estVide(int val)
{
	return val == 0 || val == 3 || val == 2;
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
