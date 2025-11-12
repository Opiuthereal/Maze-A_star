#include<iostream>
#include "agent.h"
#include"labyrinth.h"

using namespace std;

void	stat()
{
	int dep = 0;
	int moyenne = 0;
	int maxDep = 0;
	int minDep = -1;
	for (int i = 0; i < 100; i++)
	{
		Maze m("source.mz");
		Agent agent(m);
		dep = agent.wayRand(m);
		moyenne += dep;
		if (dep > maxDep)
			maxDep = dep;
		else if (dep < minDep || minDep == -1)
			minDep = dep;
		cout << "Essai " << i+1 << ": " << dep << " déplacements\n";
	}
	moyenne = moyenne/100;
	cout << "\nnombre d'essais: 100\n" << "Moyenne: " << moyenne << " pas\n" << "Maximum déplacements: " << maxDep << " pas\n" << "Minimum déplacement: " << minDep << " pas" << endl;
}

int main() 
{
	//si besoin d'afficher, il faut aussi retirer les lignes commentés dans les 4 if/else de agent.cpp démarrant ligne 77
	/*Maze m("source.mz");
	Agent agent1(m);
	cout << agent1;
	cout << m;
	agent1.wayRand(m);*/
	
	stat();
	return 0;
}
