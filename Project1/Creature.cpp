#include "Creature.h"
#include "ThePacmanGame.h"
#include "SmartStrategy.h"
#include "NormalStrategy.h"
#include "InputStrategy.h"

Creature::Creature(char _creatureIcon, int _creatureStrategyType, MoveStrategy* _mvStrategy, Colors _creatureColor, Direction _creatureDirection)
	: creatureIcon(_creatureIcon), creatureStrategyType(_creatureStrategyType), mvStrategy(_mvStrategy), creatureColor(_creatureColor), creatureDirection(_creatureDirection) {}

Creature::~Creature()
{
	delete mvStrategy;
}

void Creature::initCreature(GameBoard& board, char _creatureIcon) 
{
	creatureColor = Colors::WHITE;
	if (creatureStrategyType == DYNAMIC)
	{
		hasIntervalTime = true;
		creatureStrategyType = SMART;
	}

	setMoveStrategy();
	collectCreatureStartingPos(board);
	board.setCellInBoard(startingPos, GameBoard::BREADCRUMB);
	resetCreaturePosition();
	prevPos = currPos;
	nextPosIsValid = false;
}

void Creature::setMoveStrategy() //set move strategy according to creatureStrategyType
{
	delete mvStrategy;
	switch (creatureStrategyType)
	{
	case SMART:
		mvStrategy = new SmartStrategy;
		if (hasIntervalTime)
			mvStrategy->setMoveInterval(20);
		break;
	case NORMAL:
		mvStrategy = new NormalStrategy;
		if (hasIntervalTime)
			mvStrategy->setMoveInterval(15);
		break;
	case INPUT:
		mvStrategy = new InputStrategy;
		break;
	default: //NONE
		mvStrategy = nullptr;
		break;
	}
}

void Creature::collectCreatureStartingPos(GameBoard& board)
{
	startingPos = board.collectStartingPos(creatureIcon);
}

void Creature::replaceStrategyIfNeeded()
{
	if (hasIntervalTime && mvStrategy->getMoveInterval() <= 0)
	{
		if (creatureStrategyType == SMART)
			creatureStrategyType = NORMAL;
		else if (creatureStrategyType == NORMAL)
			creatureStrategyType = SMART;

		setMoveStrategy();
	}
}

void Creature::move(GameBoard& board, const Position& pacmanPos)
{
	replaceStrategyIfNeeded();
	mvStrategy->executeMove(*this, board, pacmanPos);
	//afterMoveProcedure(board);
}

void Creature::updateIntervalInStrategyIfNeeded()
{
	if (hasIntervalTime)
		mvStrategy->setMoveInterval((mvStrategy->getMoveInterval() - 1));
}

void Creature::afterMoveProcedure(GameBoard& board)
{
	//Final Part
	gotoxy(prevPos.getXPos(), prevPos.getYPos());
	//The creatured will move and we want to print the cell as it were before.
	if (board.getCellInBoard(prevPos) == GameBoard::BREADCRUMB)
	{
		if (ThePacmanGame::isGameColorized())
			setTextColor(board.getBreadcrumbColor());

		cout << GameBoard::BREADCRUMB;
	}
	else
		cout << GameBoard::SPACE;
}

void Creature::resetAfterInvalidNextPos()
{
	nextPos = currPos;
	if (creatureIcon != GHOST)
		creatureDirection = Direction::STAY;
}

void Creature::resetCreaturePosition()
{
	//currPos should changed to startingPos
	//NextPos should changed also to currPos
	currPos = startingPos;
	nextPos = currPos;
	creatureDirection = Direction::STAY;
}

void Creature::setCurrPos(int x, int y)
{
	currPos.setXPos(x);
	currPos.setYPos(y);
}

void Creature::setCreatureNextPos(GameBoard& board)
{
	nextPos.setNextPos(creatureDirection, creatureIcon, board); 
}

bool Creature::isCreaturePositionValid(GameBoard& board)
{
	return nextPos.isPositionValid(board, creatureIcon);
}

void Creature::printCreature() const
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (ThePacmanGame::isGameColorized()) { setTextColor(creatureColor); }
	cout << creatureIcon;
}