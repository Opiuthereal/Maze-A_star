#include "node.h"
#include <iostream>
#include <cmath>

// Constructeur
Node::Node(int pos, int entree, int sortie)
{
	int x = pos % 21;
	int y = pos / 21;
	
	_pos = pos;
	//Distance de Manhattan
	_g = sqrt(pow((entree % 21)-x, 2) + pow((entree / 21)-y, 2)); 
	_h = sqrt(pow((sortie % 21)-x, 2) + pow((sortie / 21)-y, 2));
	_f = _g + _h;
}

//Getters
int	Node::getF() const	{ return _f; }
int	Node::getH() const	{ return _h; }
int	Node::getG() const	{ return _g; }
int	Node::getPos() const	{ return _pos; }
