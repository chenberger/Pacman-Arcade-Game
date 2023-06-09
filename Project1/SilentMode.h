#pragma once

#include "ThePacmanGame.h"
#include <fstream>


using std::ifstream;

class SilentMode : public ThePacmanGame
{
protected:
	int currStepsFile = 0;
	int currResultFile = 0;
	int stepsCounter = 0;
	bool testPassed = true;
	Direction direction;
	ifstream stepsFile;
	ifstream resultFile;
	vector <string> stepsfilesArr;
	vector <string> resultfilesArr;
	vector <bool> testScreen;

public:
	virtual void run() override;
	virtual void runAllSessions() override;
	virtual void runSingleScreensSession() override;
	virtual void runGame() override;
	virtual void singleFruitSession() override;
	virtual void singleCreaturesIteration() override;
	virtual void completeGhostsSession() override;
	virtual void completePacmanSession() override; 
	virtual void completeFruitSession() override;

	//virtual void testResultProcedure();
	void handleInvalidScreen();
	void setLivesLeftFromResFile();
	void setAllCreaturesMoveStrategy();
	void loadAllStepsAndResultFiles();
	void openFilesForRead();
	void closeCurrFiles();
	void readInfoFromStepsFile();
	void convertInputToDirection(string _dir);
	int convertStrToNum(string numToConvert);
	void setPacDirectionFromFile();
	void setGhostsDirectionFromFile();
	void setFruitDirectionFromFile();
	void comparestepsToResultFile();
	void printAfterTest();
};