#pragma once

namespace RocketFrog
{
#define NUM_ROWS 9
#define NUM_COLS 9

	class SudokuSolver
	{
	public:
		SudokuSolver(const char* a_sFileName);
		~SudokuSolver();
		bool Solve();
		void Print() const;

	private:
		SudokuSolver();
		bool ReadFile(const char* a_sFileName);
		bool IsConfilcted(const int a_row, const int a_col, const int a_val) const;
		bool IsRowConflict(const int a_row, const int a_val) const;
		bool IsColumnConflict(const int a_col, const int a_val) const;
		bool IsSquareConflict(const int a_row, const int a_col, const int a_val) const;
		bool FindUnassignedLocation(int* a_row, int* a_col) const;

		int m_grid[NUM_ROWS][NUM_COLS];
	};
}