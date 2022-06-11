#pragma once

#include "Board.h"

namespace nadpher
{

class Solver
{
public:
	Solver() = delete;
	Solver(Board& board)
		: board_(board)
	{}

	bool solve(unsigned int index=0);

private:
	Board& board_;
};

}

