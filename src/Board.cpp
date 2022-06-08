#include "Board.h"

#include <cstdio>

namespace nadpher
{

Board::Board()
{
	board_.fill(0);
}

void Board::setCell(unsigned int value, const Coord& pos)
{
	const unsigned int maxCellValue = 9;

	if (!checkPosition(pos))
	{
		return;
	}

	if (value > maxCellValue)
	{
		std::printf("Invalid value\n");
		return;
	}

	board_[pos.x + pos.y * boardLength] = value;
}

bool Board::checkPosition(const Coord& pos) const
{
	if (pos.x >= boardLength || pos.y >= boardLength)
	{
		std::printf("Invalid position\n");
		return false;
	}

	return true;
}

unsigned int Board::readCell(const Coord& pos) const
{
	if (!checkPosition(pos))
	{
		return 0;
	}

	return board_[pos.x + pos.y * boardLength];
}

}