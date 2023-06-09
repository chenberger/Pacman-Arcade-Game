#pragma once

#include "SimpleMode.h"
#include <cstdio>
#include <fstream>

using std::ofstream;

class SaveMode : public SimpleMode
{
	string dir;
	int countsteps = 0;
	ofstream stepsFile;
	ofstream resultFile;

public:

	virtual void run() override;
	void resetStepsCounter() { countsteps = 0; }
	void openFilesForWriting();
	void convertDirToInput(Direction _dir);
	virtual void runGame() override;

	void writeLivesLeftToResultFile();
	void writeToResultFileEndOfSession();
	void writeToResultFileDuringSession();
	void writeToResultFileInvalidBoard();
	void removeOldFiles();
	virtual void singleCreaturesIteration() override;
	virtual void completeGhostsSession() override;
	virtual void completePacmanSession() override;
	virtual void completeFruitSession() override;
	void WritePacmanMoveToStepsFile();
	void WriteGhostsMoveToStepsFile();
	void WriteFruitMoveToStepsFile();
	void closeFiles();

};
