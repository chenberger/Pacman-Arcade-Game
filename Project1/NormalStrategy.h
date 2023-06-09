#pragma once
#include "MoveStrategy.h"

class Creature;

class NormalStrategy : public MoveStrategy
{
private:
	int normalMoveInterval = 0;
public:
	~NormalStrategy()override {};
	virtual void setMoveInterval(int _mvInterval) override { normalMoveInterval = _mvInterval; }
	virtual int getMoveInterval() const override { return normalMoveInterval; }
	virtual void executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos) override;
	void generateRandomDirection(Creature& creature);
};
