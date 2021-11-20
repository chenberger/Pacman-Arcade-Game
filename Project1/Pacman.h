﻿#pragma once

#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"

using std::cout;
using std::endl;

class Pacman 
{
public:
	static constexpr char PACMAN = '@';

private:
	Colors pacmanColor = Colors::WHITE;
	Position currPos, nextPos;
	Direction pacmanDirection = Direction::STAY; 
	int livesLeft = 3;
	int score = 0;

public:
	
	void initPacman(); 
	void movePacman(GameBoard& board);
	void updateLivesLeft() { livesLeft--; }
	void updatePos() { currPos = nextPos; };
	void updateScore(GameBoard& board);
	void printPacman() const;

	//Get-Set Functions
	void setPacmanPosition();
	void setDirection(Direction dir);
	void setPacColor(Colors color = Colors::WHITE) { pacmanColor = color; }
	Position getCurrPos() const { return currPos; }
	Direction getDirection (char key) const;
	int getScore() const { return score; }
	int getLivesLeft() const { return livesLeft; }
	Colors getPacColor() const { return pacmanColor; }
};
