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
	int i;
	ifstream f(maze_name);

for (i=0; i<21*12 ; i++) 
{
	f >> _tab[i];
	//cout << _tab[i]; SAFE
	/*if (_tab[i] == 0)  _map[i] = '.';
	if (_tab[i] == 1) _map[i] = '|';
	if (_tab[i] == 2) _map[i] = 'E';
	if (_tab[i] == 3) _map[i] = 'S';*/
}

	for (i=0; i<21*12; i++)
	{
		//cout << i << endl; SAFE
		if (!estVide(_tab[i])) //on garde les points en points
			_map[i] = changeToTileset(_map, _tab, i); //PROBLEME
	}

	f.close();
}

const char* Maze::changeToTileset(const char* map[21*12], int map2[21*12], int i)
{
	int		haut;
	int		bas;
	int		droite;
	int		gauche;
	const char* 	line = "\xE2\x94\x80";
	const char* barre = "\xE2\x94\x82";
	const char*	coin_hg = "\xE2\x94\x8c";
	const char*	coin_hd = "\xE2\x94\x90";
	const char*	coin_bd = "\xE2\x94\x94";
	const char*	coin_bg = "\xE2\x94\x98";
	const char*	barre_g = "\xE2\x94\xA4";
	const char*	barre_b = "\xE2\x94\xAC";
	const char*	barre_h = "\xE2\x94\xB4";
	const char*	plus = "\xE2\x94\xBC";
	const char* 	barre_d = "\xE2\x94\x9C";
	if (i == 0) //coin de haut-gauche
	{
		droite = map2[i + 1];
		bas = map2[i + 21];

		//cout << i << ";" << map2[i] << endl;
		//cout << droite << "d;b" << bas << endl;
		// SAFE
		if (droite == 1 && estVide(bas))
			return line;
		else if (estVide(droite) && bas == 1)
			return barre;
		else
			return coin_hg;

	}
	else if (i+1  == 21) //coin de haut-droite
	{
		gauche = map2[i - 1];
                bas = map2[i + 21];

		//cout << i << ";" << map2[i] << endl;
		//cout << gauche << "g;b" << bas << endl;
		//SAFE
                if (gauche == 1 && estVide(bas))
			return line;
                else if (estVide(haut) && bas == 1)
                        return barre;
                else
                        return coin_hd;

	}
	else if (i+1 == 11*21) //coin bas-gauche
	{
                droite = map2[i + 1];
                haut = map2[i - 21];

		//cout << i << ";" << map2[i] << endl;
		//cout << droite << "d;h" << haut << endl;
		// SAFE
                if (droite == 1 && estVide(haut))
                        return line;
                else if (estVide(droite) && haut == 1)
                        return barre;
                else
                        return coin_bg;

        }

	else if (i+1 == 12*21) //coin de bas-droite
	{
                gauche = map2[i - 1];
                haut = map2[i - 21];
		//cout << i << ";" << map2[i] << endl;
		//cout << gauche << "g;h" << haut << endl;
		// SAFE
                if (gauche == 1 && estVide(haut))
			return line;
                else if (estVide(gauche) && haut == 1)
                        return barre;
                else
                        return coin_bd;

        }

	else if (i > 0 && i+1 <21) //ligne haut
	{
		droite = map2[i + 1];
		gauche = map2[i - 1];
		bas = map2[i + 21];
		//cout << i << ";" << map2[i] << endl;
		//cout << droite << "d;g" << gauche << ";b"<< bas << '\n' << endl;
		// SAFE
		if (estVide(droite) && estVide(gauche) && bas == 1)
			return barre_b;
		else if (estVide(gauche) && droite == 1 && bas == 1)
			return coin_hg;
		else if (gauche == 1 && estVide(droite) && bas == 1)
			return coin_hd;
		else
			return line;
	}
	else if (i+1 > 11*21 && i+1 < 12*21) //ligne bas
        {
                droite = map2[i + 1];
                gauche = map2[i - 1];
                haut = map2[i - 21];
                if (estVide(droite) && estVide(gauche) && haut == 1)
                        return barre_h;
                else if (estVide(gauche) && droite == 1 && haut == 1)
                        return coin_bg;
                else if (gauche == 1 && estVide(droite) && haut == 1)
                        return coin_bd;
                else
                        return line;
        }
	else if (i+1 % 21 == 1)//ligne gauche
        {
                droite = map2[i + 1];
                bas = map2[i + 21];
                haut = map2[i - 21];
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
	else if (i+1 % 21 == 0)//ligne de droite
        {
                gauche = map2[i - 1];
                bas = map2[i + 21];
                haut = map2[i - 21];
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
	else //au centre
	{
		droite = map2[i + 1];
		gauche = map2[i - 1];
		bas = map2[i + 21];
		haut = map2[i - 21];

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
	return " ";
}

bool	Maze::estVide(int val)
{
	return val == 0 || val == 3 || val == 2;
}


//Surcharge --> Affichage
ostream& operator << (ostream& os, const Maze& m){
	int	i;

	/*for (i=0; i<21*12 ; i++) 
	{
	if (i%21 == 0) cout<< endl;
		os << m._map[i] << "";
	}	
	cout <<endl;*/
	for (i=0; i<21*12-1 ; i++) 
	{
	if (i%21 == 0) cout<< endl;
		os << m._map[i] << "";
	}	
	cout <<endl;
	return os;
} 

int main() 
{
	Maze m("source.mz");
	cout << m;
	return 0;
}
