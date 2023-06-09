#pragma once
#include "Utilities.h"
#include "Position.h"
#include "GameBoard.h"
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class Creature;

class MoveStrategy
{
public:
	virtual ~MoveStrategy() {};
	virtual void setMoveInterval(int _mvInterval) = 0;
	virtual int getMoveInterval() const = 0;
	virtual void executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos) = 0;
};