#include "SilentMode.h"
#include "LoadMode.h"

void SilentMode::run()
{
	cout << "Silent Mode" << endl;
	Sleep(2000);
	clearScreen();
	runAllSessions();
}

void SilentMode::runAllSessions()
{
	loadScreens();
	loadAllStepsAndResultFiles();

	runSingleScreensSession();
	goodBye();
}

void SilentMode::runSingleScreensSession()
{
	string currObj;
	//Typeid helper
	currObj = typeid(*this).name();
	currObj = currObj.substr(6);
	pacmanDied = false;

	for (currStepsFile = 0, currResultFile = 0; currStepsFile < stepsfilesArr.size() && activate; currStepsFile++, currResultFile++)
	{
		handleInvalidScreen();
		initSingleScreen();
		if (game_board.isValidBoard())
		{
			testPassed = true;
			setAllCreaturesMoveStrategy();
			runSingleScreen();
		}
		else
		{
			--currResultFile;
			--currStepsFile;
		}
	}
}

void SilentMode::runGame()
{
	openFilesForRead();
	setLivesLeftFromResFile();

	string currObj;
	//Typeid helper
	currObj = typeid(*this).name();
	currObj = currObj.substr(6);

	stepsCounter = 0;
	bool endFile = false;
	do
	{
		stepsCounter++;
		try
		{

			readInfoFromStepsFile();

			if (currObj == "LoadMode")
				ThePacmanGame::singleCreaturesIteration();
			else
				singleCreaturesIteration();

			if (collisionInCurrStepIndicator)
				comparestepsToResultFile();
		}
		catch (...)
		{
			endFile = true;
		}


	} while (!GameFinished() && testPassed && !endFile);

	comparestepsToResultFile();
	printAfterTest();
	closeCurrFiles();
	return;
}

void SilentMode::singleCreaturesIteration()
{
	singleGhostsSession();
	completeGhostsSession();
	singlePacmanSession();
	completePacmanSession();
	singleFruitSession();
}

void SilentMode::completeGhostsSession()
{
	if (j == 0)
		j = 1;
	else
		j = 0; //they won't move in the next step

	if (isFruitEatenByGhost())
		fruit.disableActivity();

	if (checkCollision())
		collisionProcedure();
}

void SilentMode::completePacmanSession()
{
	if (isFruitEatenByPacman())
		fruit.disableActivity();

	if (!checkCollision())
		updateScoreAndBoardAfterPacman();
	else
	{
		collisionProcedure();
	}
}

void SilentMode::singleFruitSession()
{
	if (fruit.isActive())
	{
		if (fruitTurn)
		{
			//To all modes
			fruit.move(game_board);
			fruit.updatePrevPos();
			fruit.updatePos();
			fruitTurn = false;
			fruit.afterMoveProcedure(game_board);
		}
		else
			fruitTurn = true;


		completeFruitSession();
		fruit.ReduceTimeOnBoard();

		if (fruit.getTimeOnBoard() == 0)
		{
			fruit.updatePrevPos();
			fruit.afterMoveProcedure(game_board);
			fruit.disableActivity();
		}

	}

}

void SilentMode::completeFruitSession()
{
	//fruit.afterMoveProcedure(game_board);
	if (fruit.isActive())
	{
		if (isFruitEatenByPacman() || isFruitEatenByGhost())
		{
			fruit.disableActivity();
			return;

		}

		string currObj = typeid(*this).name();
		currObj = currObj.substr(6);

		if (currObj != "SilentMode")
		{
			fruit.printCreature();
		}

	}
}



void SilentMode::setAllCreaturesMoveStrategy()
{
	pacman.setCreatureStrategyType(Creature::INPUT);
	pacman.setMoveStrategy();
	for (int i = 0; i < numOfGhosts; i++)
	{
		ghost[i].setCreatureStrategyType(Creature::INPUT);
		ghost[i].setMoveStrategy();
	}
	fruit.setCreatureStrategyType(Creature::INPUT);
	fruit.setMoveStrategy();
}

void SilentMode::loadAllStepsAndResultFiles()
{
	string path;
	for (const auto& file : filesystem::directory_iterator("."))
	{
		if (file.path().string().ends_with(".steps"))
		{
			path = file.path().string();
			path.erase(0, 2);
			stepsfilesArr.push_back(path);
		}
		else if (file.path().string().ends_with(".result"))
		{
			path = file.path().string();
			path.erase(0, 2);
			resultfilesArr.push_back(path);
		}
	}
	std::sort(stepsfilesArr.begin(), stepsfilesArr.end());
	std::sort(resultfilesArr.begin(), resultfilesArr.end());
}

void SilentMode::openFilesForRead()
{
	stepsFile.open(stepsfilesArr[currStepsFile]);
	resultFile.open(resultfilesArr[currResultFile]);
}

void SilentMode::closeCurrFiles()
{
	stepsFile.close();
	resultFile.close();
}

void SilentMode::readInfoFromStepsFile()
{
	setGhostsDirectionFromFile();
	setPacDirectionFromFile();
	setFruitDirectionFromFile();
}

int SilentMode::convertStrToNum(string numToConvert)
{
	int res = 0;
	int i = 0;
	while (numToConvert[i] != '\n')
	{
		if (isdigit(numToConvert[i]))
		{
			res += res * 10 + numToConvert[i] - '0';
		}
	}
	return res;
}

void SilentMode::setPacDirectionFromFile()
{
	string line;
	string subStr;
	getline(stepsFile, line);
	subStr = line.substr(8, 12);
	convertInputToDirection(subStr);
	pacman.setDirection(direction);
}

void SilentMode::setGhostsDirectionFromFile()
{
	string line;
	string subStr;
	for (int i = 0; i < numOfGhosts; i++)
	{
		getline(stepsFile, line);
		subStr = line.substr(8, 12);
		convertInputToDirection(subStr);
		ghost[i].setDirection(direction);
	}
}

void SilentMode::setFruitDirectionFromFile()
{
	string line;
	string subStr;

	getline(stepsFile, line);
	subStr = line.substr(8, 11);
	convertInputToDirection(subStr);
	fruit.setDirection(direction);

	//handles the case when the fruit born
	subStr = line.substr(11);
	//if (subStr[0] != '\0') //)//(!subStr.starts_with('\n'))
	if (isdigit(line[line.length() - 1]))
	{

		subStr = line.substr(15, 16);
		int xPos = stoi(subStr);
		subStr = line.substr(18, 19);
		int yPos = stoi(subStr);
		fruit.setCurrPos(xPos, yPos);
		fruit.updatePrevPos();
		fruit.setNextPos(fruit.getCurrPos());
		subStr = line.substr(24);
		fruit.setFruitVal(stoi(subStr));
		fruit.enableActivity();
		fruitTurn = false;
		fruit.setTimeOnBoard(40);
	}
}

void SilentMode::comparestepsToResultFile()
{
	int numOfStepsInFile;
	string line;
	string subStr;

	getline(resultFile, line); 
	size_t last_index = line.find_last_not_of("0123456789");
	subStr = line.substr(last_index + 1);

	numOfStepsInFile = stoi(subStr);

	if (numOfStepsInFile == stepsCounter || numOfStepsInFile - 1 == stepsCounter || numOfStepsInFile == stepsCounter - 1)
		testPassed = true;
	else
		testPassed = false;

	collisionInCurrStepIndicator = false;
}

void SilentMode::printAfterTest()
{
	clearScreen();
	if (testPassed)
		cout << "Test passed" << endl;
	else
		cout << "Test failed" << endl;

	Sleep(2000);
	clearScreen();
}

void SilentMode::convertInputToDirection(string _dir)
{

	if (_dir == "UP   ")
		direction = Direction::UP;

	else if (_dir == "DOWN ")
		direction = Direction::DOWN;

	else if (_dir == "LEFT ")
		direction = Direction::LEFT;

	else if (_dir == "RIGHT")
		direction = Direction::RIGHT;

	else
		direction = Direction::STAY;

}

void SilentMode::handleInvalidScreen()
{
	string tempTemplate = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr
	(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 7));

	string tempstepsFile = stepsfilesArr[currStepsFile].substr(0, stepsfilesArr[currStepsFile].size() - 6);


	while (tempstepsFile != tempTemplate && currStepsFile < stepsfilesArr.size())
	{

		game_board.moveToNextTemplate();

		tempTemplate = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr
		(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 7));
		tempstepsFile = stepsfilesArr[currStepsFile].substr(0, stepsfilesArr[currStepsFile].size() - 6);
	}

}

void SilentMode::setLivesLeftFromResFile()
{
	int livesLeft;
	string line;
	string subStr;
	getline(resultFile, line);
	size_t last_index = line.find_last_not_of("0123456789");
	subStr = line.substr(last_index + 1);
	livesLeft = stoi(subStr);
	pacman.setLivesLeft(livesLeft);
}

