#include<iostream>
#include "agent.h"

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
		//Je part du postulat qu'un labyrinth à toujours une entrée
		int i = -1;
		while (m.getTab(++i) != 2);
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

// update la pos de l'agent
void	Agent::setAgent(int i, Maze& m)
{
	//A FAIRE: Remettre le char du joueur précédent en entrée ou en espace
	_val = i;
	_nord = (i >= 21) ? m.getTab(i-21) : 1;
	_sud = (i <= 11*21-1) ? m.getTab(i+21) : 1;
	_est = (i % 21 != 20) ? m.getTab(i+1): 1;
	_ouest = (i % 21 == 0) ? m.getTab(i-1) : 1;
	m.setMap(i , "\xE2\x80\xA2"); // •
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
