#include "SudokuSolver.h"
#include <stdlib.h>

void main()
{
	//RocketFrog::SudokuSolver _solver("sudokuSample.txt");
	RocketFrog::SudokuSolver _solver("check.txt");
	if (_solver.Solve())
	{
		_solver.Print();
	}

	system("PAUSE");
}