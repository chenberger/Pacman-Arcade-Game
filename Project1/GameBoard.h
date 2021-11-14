#pragma once
using namespace std;

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Position.h"


class Position; //Forward declaration.

const int ROWMAX = 25;
const int COLMAX = 80;


//enum symbols { SPACE = ' ', BORDER = 219, BREADCRUMB = '*', TUNNEL = '|' };
//enum directions { UP = 119, DOWN = 120, LEFT = 97, RIGHT = 100, STAY = 115 };

class GameBoard
{
private:
	char _board[ROWMAX][COLMAX];
	int totalBreadcrumbs = 0;
	//Color = ?

public:

	void initBoard();
	void initOuterBorders();
	void initInnerWalls();
	//void initInvisibleTunnels();
	void initBreadcrumbs();
	void printBoard();
	int getBreadcrumbs() { return totalBreadcrumbs - 1000; }
	void setCellInBoard(int& x, int& y, char ch) { _board[y][x] = ch; }
	void setCellInBoard(Position& pos, char ch);
	char getCellInBoard(int x, int y) { return _board[y][x]; }
	char getCellInBoard(Position& pos) const;
};