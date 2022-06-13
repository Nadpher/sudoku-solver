#include "Solver.h"

namespace nadpher
{


// TODO: FIX THIS
bool Solver::solve(unsigned int index)
{
	Coord pos = { index % Board::boardLength, index / Board::boardLength };

	// if last cell
	if (index == (Board::boardLength * Board::boardLength) - 1)
	{
		if (board_.readCell(pos))
		{
			return true;
		}

		for (int i = 1; i <= Board::boardLength; ++i)
		{
			board_.setCell(i, pos);

			if (board_.checkCell(pos))
			{
				return true;
			}
		}
	}
	else
	{
		if (board_.readCell(pos))
		{
			if (solve(index + 1))
			{
				return true;
			}
		}

		for (int i = 1; i <= Board::boardLength; ++i)
		{
			board_.setCell(i, pos);

			if (board_.checkCell(pos))
			{
				if (solve(index + 1))
				{
					return true;
				}
			}
		}
	}

	board_.setCell(0, pos);
	return false;
}

}