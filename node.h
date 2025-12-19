#include <iostream>
#pragma once
#include <iostream>

class Node {
	private:
		int _pos;
		int _g;
		int _h;
		int _f;

	public:
			Node(int pos, int posEntree, int posSortie);
		int	getPos() const;
		int	getF() const;
		int	getG() const;
		int	getH() const;
};
