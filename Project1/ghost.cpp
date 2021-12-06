#include "Ghost.h"
#include "ThePacmanGame.h"


Ghost::Ghost(Position _ghostCurrPos, Position _ghostNextPos, Direction _ghostDirection, Colors _ghostColor, char _ghostIcon)
	: Creature(_ghostColor, _ghostCurrPos, _ghostNextPos, _ghostDirection, _ghostIcon)
{
}

void Ghost::initGhost()
{
	setColor(Colors::WHITE);
	resetCreaturePosition();

}

/*void Ghost::setGhostPosition(int xCoord, int yCoord)
{
	currPos.setXPos(xCoord);
	currPos.setYPos(yCoord);
	nextPos = currPos;
}*/

void Ghost::moveGhost(GameBoard& board)
{
	bool isValid = false;
	while (!isValid)
	{
		//Set potential new position to ghost, then check if it's valid.
		generateRandomDirection();
		setCreatureNextPos();
		isValid = isCreaturePositionValid(board);
		if (!isValid) //Rollback, before starting the loop again.
			resetNextPos();
	}

	//The ghost printed and we want the print the cell as it were before.
	gotoxy(getCurrPos().getXPos(), getCurrPos().getYPos());
	if (board.getCellInBoard(getCurrPos()) == GameBoard::BREADCRUMB)
	{
		if (ThePacmanGame::isGameColorized())
			setTextColor(board.getBreadcrumbColor());
		cout << GameBoard::BREADCRUMB;
	}
	else
		cout << GameBoard::SPACE;
}

/*void Ghost::printGhost() const
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (ThePacmanGame::isGameColorized())
		setTextColor(ghostColor);
	cout << GHOST;
}*/

void Ghost::generateRandomDirection()
{
	int dirInd = rand() % 4 + 1;
	switch (dirInd)
	{
	case 1:
		setDirection(Direction::UP);
		break;
	case 2:
		setDirection(Direction::DOWN);
		break;
	case 3:
		setDirection(Direction::LEFT);
		break;
	case 4:
		setDirection(Direction::RIGHT);
		break;
	default:
		break;
	}

	setDirection(ghostDirection);
}