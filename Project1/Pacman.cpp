#include "Pacman.h"
#include "ThePacmanGame.h"

Pacman::Pacman(Position _pacmanCurrPos, Position _pacmanNextPos, Direction _pacmanDirection 
	,Colors _pacmanColor, char _pacmanIcon)
	: Creature(_pacmanColor, _pacmanCurrPos, _pacmanNextPos, _pacmanDirection, _pacmanIcon)
{
	/*livesLeft = 3;
	score = 0;*/
}

//Pacman::Pacman(Position _pacmanCurrPos, Position _pacmanNextPos, Direction _pacmanDirection = Direction::STAY
//	, Colors _pacmanColor = Colors::WHITE, char _pacmanIcon = '@')

void Pacman::initPacman()
{
	score = 0;
	livesLeft = 3;
	pacmanColor = Colors::WHITE;
	setPacmanPosition();
}

void Pacman::setPacmanPosition()
{
	currPos.setXPos();
	currPos.setYPos();
	nextPos = currPos;
	pacmanDirection = Direction::STAY;
}

void Pacman::movePacman(GameBoard& board)
{
	//Set potential new position to pacman, then check if it's valid.
	setCreatureNextPos();
	//nextPos.setNextPos(pacmanDirection, PACMAN);
	if ( getDirection() != Direction::STAY && isCreaturePositionValid(board) ) //So we should move the pacman
	{
		//print space in current position because soon the pacman will be moved.
		gotoxy( getCurrPos().getXPos(), getCurrPos().getYPos() );
		cout << GameBoard::SPACE;
	}
	else //In case not, please stay on the current position. + Rollback to nextPos
	{
		resetNextPos();
		setDirection(Direction::STAY);
	}
}

void Pacman::printPacman() const
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (ThePacmanGame::isGameColorized()) { setTextColor(pacmanColor); }
	cout << PACMAN;
}

void Pacman::updateScore(GameBoard& board)
{
	//Collect score if breadCrumb placed in currPos
	if (board.getCellInBoard(nextPos) == GameBoard::BREADCRUMB)
		score++;
}

//Direction Pacman::getDirection(char key) const
//{
//	//Key translation to Direction
//	switch (key)
//	{
//	case 'w':
//	case 'W':
//		return Direction::UP;
//	case 'x':
//	case 'X':
//		return Direction::DOWN;
//	case 's':
//	case 'S':
//		return Direction::STAY;
//	case 'd':
//	case 'D':
//		return Direction::RIGHT;
//	case 'a':
//	case 'A':
//		return Direction::LEFT;
//	default:
//		return Direction::WRONG_KEY;
//	}
//}

void Pacman::setDirection(Direction dir)
{
	pacmanDirection = dir;
}