#include<iostream>
#include "agent.h"
#include "node.h"
#include <cstdlib>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <stack>
#include <vector>

using namespace std;

	Agent::Agent()
{
	_nord = -1;
	_sud = -1;
	_est = -1;
	_ouest = -1;
	_val = 0;	
}

	Agent::Agent(Maze& m)
	{
		//Je part du postula qu'un labyrinth à toujours une entrée
		int i = 0;
		_val = -1;
		while (m.getTab(i) != 2)
		{
			i++;
		}
		setAgent(i, m);
	}
	
	Agent::Agent(int n, int s, int e, int o, int v)
	{
		_nord = n;
		_sud = s;
		_est = e;
		_ouest = o;
		_val = v;
	}

	Agent::Agent(Maze& m, int v)
	{
		cout << "hello";
		setAgent(v, m);
	}

//Setters
void	Agent::setSud(int v)	{_sud = v;}
void	Agent::setNord(int v)	{_nord = v;}
void	Agent::setEst(int v)	{_est = v;}
void	Agent::setOuest(int v)	{_ouest = v;}
void	Agent::setVal(int v)	{_val = v;}

//Getters
int	Agent::getSud()		{return _sud;}
int	Agent::getNord()	{return _nord;}
int	Agent::getEst()		{return _est;}
int	Agent::getOuest()	{return _ouest;}
int	Agent::getVal()		{return _val;}

// update la pos de l'agent et l'affiche
void	Agent::setAgent(int i, Maze& m)
{
	if (_val != -1)
	{
		m.setPassage(_val);
		m.setColor(_val);
	}
	_val = i;
	_nord = (i >= 21) ? m.getTab(i-21) : 1;
	_sud = (i <= 11*21-1) ? m.getTab(i+21) : 1;
	_est = (i % 21 != 20) ? m.getTab(i+1): 1;
	_ouest = (i % 21 != 0) ? m.getTab(i-1) : 1;
	m.setMap(i , "\xE2\x80\xA2"); // •
}

int	Agent::wayRand(Maze& m)
{	
	static random_device rd;              // source de vraie randomness
	static mt19937 gen(rd());             // moteur pseudo-aléatoire
	uniform_int_distribution<> dis(0, 3); // valeurs de 0 à 3
	int coups = 0;
	int randMove; // nombre aléatoire entre 0 et 3
	
	while(m.getTab(_val) != 3)
	{
		randMove = dis(gen); //génère un nombre aléatoir de 0 à 3
		if (randMove == 0 && (_nord == 0 || _nord == 2 || _nord == 3))
		{
			//mis en haut pour évter d'effacer la dernière ligne
			system("clear");
			setAgent(_val-21 , m);
			cout << m << endl;
			coups++;
			cout << "nombre de déplacement:" << coups << endl;
			//this_thread::sleep_for(chrono::milliseconds(10));
		}	
		else if (randMove == 1 && (_est == 0 || _est == 2 || _est == 3))
		{
			//mis en haut pour évter d'effacer la dernière ligne
			system("clear");
			setAgent(_val + 1 , m);
			cout << m << endl;
			coups++;
			cout << "nombre de déplacement:" << coups << endl;
			//this_thread::sleep_for(chrono::milliseconds(10));
		}	
		else if (randMove == 2 && (_sud == 0 || _sud == 2 || _sud == 3))
		{
			//mis en haut pour évter d'effacer la dernière ligne
			system("clear");
			setAgent(_val+21 , m);
			cout << m << endl;
			coups++;
			cout << "nombre de déplacement:" << coups << endl;
			//this_thread::sleep_for(chrono::milliseconds(10));
		}	
		else if (randMove == 3 && (_ouest == 0 || _ouest == 2 || _ouest == 3))
		{
			//mis en haut pour évter d'effacer la dernière ligne
			system("clear");
			setAgent(_val-1 , m);
			cout << m << endl;
			coups++;
			cout << "nombre de déplacement:" << coups << endl;
			//this_thread::sleep_for(chrono::milliseconds(10));
		}
	}
	return coups;
}

bool	Agent::notIn(int val, int tab[12*21])
{
	for (int i = 0; i < 21*12; i++)
	{
		if (tab[i]==val)
		{
			return false;
		}
	}
	
	return true;
}

void	Agent::wayDFS(Maze& m)
{
	stack<int> aFaire;
	int fait[21*12];
	fill(fait, fait + 21 * 12, -1); //fonction pour remplir "fait" de -1
	int pos;
	int i = 0;
	while (m.getTab(_val) != 3)
	{
		if (notIn(_val, fait))
		{
			aFaire.push(_val);
		}
		pos = aFaire.top();
		aFaire.pop();
		fait[i] = pos;
		setAgent(pos, m);
	
		if (_nord != 1 && notIn(pos-21, fait))
		{
			aFaire.push(pos-21);
		}
		
		if (_ouest != 1 && notIn(pos-1, fait))
		{
			aFaire.push(pos-1);
		}
		
		if (_sud != 1 && notIn(pos+21, fait))
		{
			aFaire.push(pos+21);
		}
		
		if (_est != 1 && notIn(pos+1, fait))
		{
			aFaire.push(pos+1);
		}
		cout << m << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		i++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
bool Agent::IsIn(int pos, const vector<Node>& v) 
{
	for (const Node& e : v) 
	{
		if (e.getPos() == pos) 
		{
			return true;
		}
	}
	return false;
}


void Agent::wayAStar(Maze& m)
{

	int n;

	vector<Node> ouvert;
	vector<Node> fermee;

	int posE = 1;
	int posS = 250;
	int choix = 0;
	int coups = 0;

	//on push l'heuristique des cases adjacentes
	if (_nord == 0 || _nord == 3) 
	{
		ouvert.push_back(Node(_val-21, posE, posS));
	}
	if (_sud == 0 || _sud == 3) 
	{
		ouvert.push_back(Node(_val+21, posE, posS));
	}
	if (_est == 0 || _est == 3) 
	{
		ouvert.push_back(Node(_val+1, posE, posS));
	}
	if (_ouest == 0 || _ouest == 3) 
	{
		ouvert.push_back(Node(_val-1, posE, posS));
	}
	//on mets l'entrée dans fermée
	fermee.push_back(Node(_val, posE, posS));

	
	while (!ouvert.empty() && _val != posS)
	{
		choix=0;
		//trouver la meilleure heuristique existante
		for (int i = 1; i < ouvert.size(); i++)
		{
			if (ouvert[i].getF() < ouvert[choix].getF())
			{
				choix = i;
			}
			else if (ouvert[i].getF() == ouvert[choix].getF() && ouvert[i].getH() < ouvert[choix].getH())
			{
				choix = i;
			}
		}
		
		n = ouvert[choix].getPos();
		setAgent(n, m);
		
		//on ajoute les heuristiques qui n'existent pas encore
		if ((_nord == 0 || _nord == 3) && !IsIn(_val-21, fermee) && !IsIn(_val-21, ouvert)) 
		{
			ouvert.push_back(Node(_val-21, posE, posS));
		}
		if ((_sud == 0 || _sud == 3) && !IsIn(_val+21, fermee) && !IsIn(_val+21, ouvert)) 
		{
			ouvert.push_back(Node(_val+21, posE, posS));
		}
		if ((_est == 0 || _est == 3) && !IsIn(_val+1, fermee) && !IsIn(_val+1, ouvert)) 
		{
			ouvert.push_back(Node(_val+1, posE, posS));
		}
		if ((_ouest == 0 || _ouest == 3) && !IsIn(_val-1, fermee) && !IsIn(_val-1, ouvert)) 
		{
			ouvert.push_back(Node(_val-1, posE, posS));
		}

		fermee.push_back(ouvert[choix]);
		ouvert.erase(ouvert.begin() + choix);
		
		cout << m << endl;
		coups++;
		cout << "nombre de déplacement:" << coups << endl;
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}
//Operator
ostream& operator << (ostream& os, const Agent& a)
{
	os << '\t' << a._nord << "\n\n";
	if (a._val == 0)
		os << a._ouest << "\t∅\t" << a._est << "\n\n";
	else
		os << a._ouest << '\t' << a._val <<'\t' << a._est << "\n\n";
	os << '\t' << a._sud << '\n' << endl;
	return os;
}
