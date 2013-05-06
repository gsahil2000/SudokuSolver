#include "SudokuSolver.h"
#include <iostream>
#pragma warning(disable : 4996)

namespace RocketFrog
{
	SudokuSolver::SudokuSolver(const char* a_sFileName)
	{
		memset(m_grid, 0, sizeof(m_grid[0][0])*NUM_COLS*NUM_ROWS);

		if (!ReadFile(a_sFileName))
		{
			throw std::exception("File Not Found!");
		}
	}

	SudokuSolver::~SudokuSolver()
	{}

	bool SudokuSolver::ReadFile(const char* a_sFileName)
	{
		FILE* _file;
		int i = 0;

		fopen_s(&_file, a_sFileName, "r");
		if (_file == nullptr)
		{
			return false;
		}

		while (!feof(_file))
		{
			fscanf(_file, "%i %i %i  %i %i %i  %i %i %i", &m_grid[i][0], &m_grid[i][1], &m_grid[i][2], &m_grid[i][3], &m_grid[i][4], &m_grid[i][5], &m_grid[i][6], &m_grid[i][7], &m_grid[i][8]);
			i++;
		}

		return true;
	}

	bool SudokuSolver::Solve()
	{
		int _row, _col;

		/// check if we still have to solve anything.
		if (!FindUnassignedLocation(&_row, &_col))
			return true;

		for (int _val = 1; _val <= 9; ++_val)
		{
			if (!IsConfilcted(_row, _col, _val))
			{
				m_grid[_row][_col] = _val;
				if (Solve())
				{
					return true;
				}
				m_grid[_row][_col] = 0;
			}
		}

		return false;
	}

	bool SudokuSolver::FindUnassignedLocation(int* a_row, int* a_col) const
	{
		for (int i = 0; i < NUM_ROWS; ++i)
		{
			for (int j = 0; j < NUM_COLS; ++j)
			{
				if (m_grid[i][j] == 0)
				{
					*a_row = i;
					*a_col = j;
					return true;
				}
			}
		}

		return false;
	}

	bool SudokuSolver::IsConfilcted(const int a_row, const int a_col, const int a_val) const
	{
		if (IsRowConflict(a_row, a_val))
		{
			return true;
		}

		if (IsColumnConflict(a_col, a_val))
		{
			return true;
		}

		if (IsSquareConflict(a_row, a_col, a_val))
		{
			return true;
		}

		return false;
	}

	bool SudokuSolver::IsRowConflict(const int a_row, const int a_val) const
	{
		for (int _col = 0; _col < NUM_COLS; ++_col)
		{
			if (m_grid[a_row][_col] == a_val)
			{
				return true;
			}
		}

		return false;
	}

	bool SudokuSolver::IsColumnConflict(const int a_col, const int a_val) const
	{
		for (int _row = 0; _row < NUM_ROWS; ++_row)
		{
			if (m_grid[_row][a_col] == a_val)
			{
				return true;
			}
		}

		return false;
	}

	bool SudokuSolver::IsSquareConflict(const int a_row, const int a_col, const int a_val) const
	{
		int _rowMultiplier = a_row / 3;
		int _colMultiplier = a_col / 3;

		for (int _row = 0; _row < 3; ++_row)
		{
			for (int _col = 0; _col < 3; ++_col)
			{
				if (m_grid[_row + 3*_rowMultiplier][_col + 3*_colMultiplier] == a_val)
				{
					return true;
				}
			}
		}

		return false;
	}

	void SudokuSolver::Print() const
	{
		for (int i = 0; i < NUM_ROWS; ++i)
		{
			for (int j = 0; j < NUM_COLS; ++j)
			{
				std::cout << m_grid[i][j];
				if ( j != 8 && (j+1) % 3 == 0 )
				{
					std::cout << " | ";
				}
				else
				{
					std::cout << " ";
				}
			}
			std::cout << "\n";
			if ((i+1) % 3 == 0)
			{
				std::cout << std::endl;
			}
		}
	}
}