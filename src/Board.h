#pragma once

#include "Coord.h"

#include <array>

namespace nadpher
{

class Board
{
public:
	Board();

	void setCell(unsigned int value, const Coord& pos);
	unsigned int readCell(const Coord& pos) const;

	static constexpr unsigned int boardLength = 9;
private:

	bool checkPosition(const Coord& pos) const;

	std::array<unsigned int, boardLength * boardLength> board_;
};

}

