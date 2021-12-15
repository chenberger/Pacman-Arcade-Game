#pragma once
#include "MoveStrategy.h"

class NormalStrategy : public MoveStrategy
{
private:
	int normalMoveInterval = 0;
public:
	//virtual int getMoveInterval() const override { return normalMoveInterval; }
	//virtual Direction getNextDir(Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos) override;
	//virtual void executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos) override;
	virtual Position getNewPosByStrategy(const Position& creatureCurrPos, GameBoard& board,
		const Position& pacmanPos, Direction& creatureDirection, const char creatureIcon) override;
	//void generateRandomDirection(Creature& creature);
	void generateRandomDirection(Direction& creatureDirection);
};