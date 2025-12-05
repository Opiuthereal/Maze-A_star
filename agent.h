#include <iostream>
#include"labyrinth.h"
#pragma once

class Agent
{
	private:
		int	_nord;
		int	_sud;
		int	_est;
		int	_ouest;
		int	_val;

	public:
		void	setNord(int v);
		void	setSud(int v);
		void	setEst(int v);
		void	setOuest(int v);
		void	setVal(int v);
		int	getNord();
		int	getSud();
		int	getEst();
		int	getOuest();
		int	getVal();
			Agent();
			Agent(Maze& m);
			Agent(int n, int s, int e, int o, int v);
			Agent(Maze& m, int v);
		void	setAgent(int i, Maze& m);
		bool	notIn(int val, int tab[12*21]);
		int	wayRand(Maze& m);
		void	wayDFS(Maze& m);
friend std::ostream& operator << (std::ostream& os, const Agent& a);
};
