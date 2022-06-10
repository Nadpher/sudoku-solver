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

	void solve();

private:
	Board& board_;
};

}

