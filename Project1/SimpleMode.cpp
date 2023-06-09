#pragma once
#include "SimpleMode.h"

void SimpleMode::run()
{
	cout << "Simple Mode" << endl;
	Sleep(2000);
	clearScreen();
	runAllSessions();	
}

void SimpleMode::runAllSessions()
{
	preparations();
	while (activate)
	{
		presentMenu();
		handleSetGameColorized();
		firstBoardProcedure();
		runSingleScreensSession();
		resetThePacmanGame();
	}
	goodBye();
}

void SimpleMode::handleQuit()
{
	if (game_menu.getUserKey() == Menu::EXIT)
		activate = false;
}

void SimpleMode::handleSetGameColorized()
{
	if (game_menu.getUserKey() == Menu::STARTCOLORIZED)
		gameColorized = true;
}

void SimpleMode::presentMenu()
{
	game_menu.entryMenu();
	handleQuit();
}

void SimpleMode::firstBoardProcedure()
{
	if (activate)
	{
		int userChosenTemplate = game_menu.getFirstBoardChoice(game_board);
		game_board.sortByFirstBoardChosen(userChosenTemplate);
	}
}

void SimpleMode::initSingleScreen(int _level)
{
	if (activate)
	{
		handleSetGameColorized();
		level = game_menu.getGameDifficulty();
		ThePacmanGame::initSingleScreen(level);
	}
}


void SimpleMode::runSingleScreensSession()
{
	pacmanDied = false;
	for (currScreenInd = 0; currScreenInd < totalNumOfScreens && !pacmanDied && activate; currScreenInd++)
	{
		handleQuit();
		initSingleScreen();

		runSingleScreen();
		game_shell.betweenScreensProcedure(game_board, currScreenInd, pacman.getScore(), playerWon);
	}
}

void SimpleMode::preparations()
{
	hideCursor();
	init_srand();
	activate = true;
	loadScreens();
}


void SimpleMode::resetThePacmanGame()
{
	pacman.resetScoreAndLives();
	game_board.lexSort();
	game_board.resetCurrTemplate();
	playerWon = false;
}

//Running a game session, according to do-while loop condition
void SimpleMode::runGame()
{
	do
	{
		singlePlayerIteration();
		singleCreaturesIteration();
		//steps
		
	} while (!GameFinished());

	afterRunGameProcedure();
	//result
}

void SimpleMode::singlePlayerIteration()
{
	char key = 0;
	Direction currDir;
	if (_kbhit())
	{
		key = _getch();
		currDir = pacman.convertKeyToDirection(key); //A kind of key translation to move.
		if (currDir != Direction::WRONG_KEY)
			pacman.setDirection(currDir);
	}
	if (key == Menu::ESC)
	{
		game_shell.pauseGame(pacman.getLivesLeft());
		key = 0; //So pacman will continue as he was before pausing.
	}
}
