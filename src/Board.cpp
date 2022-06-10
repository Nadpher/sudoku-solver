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

	if (pos.x >= boardLength || pos.y >= boardLength)
	{
		std::printf("Invalid position\n");
		return;
	}

	if (value > maxCellValue)
	{
		std::printf("Invalid value\n");
		return;
	}

	board_[pos.x + pos.y * boardLength] = value;
}

unsigned int Board::readCell(const Coord& pos) const
{
	if (pos.x >= boardLength || pos.y >= boardLength)
	{
		std::printf("Invalid position\n");
		return 0;
	}

	return board_[pos.x + pos.y * boardLength];
}

bool Board::checkCell(const Coord& pos)
{
	unsigned int value = readCell(pos);

	//horizontal
	for (unsigned int i = 0; i < boardLength; ++i)
	{
		if (readCell({i, pos.y}) == value && i != pos.x)
		{
			return false;
		}
	}

	//vertical
	for (unsigned int i = 0; i < boardLength; ++i)
	{
		if (readCell({ pos.x, i }) == value && i != pos.y)
		{
			return false;
		}
	}

	const unsigned int macroCellSize = boardLength / 3;

	//macro cell
	Coord offset = { (pos.x / macroCellSize) * macroCellSize, (pos.y / macroCellSize) * macroCellSize};
	for (unsigned int i = 0; i < macroCellSize; ++i)
	{
		for (unsigned int j = 0; j < macroCellSize; ++j)
		{
			if (readCell({ j + offset.x, i + offset.y }) == value &&
				j + offset.x != pos.x && 
				i + offset.y != pos.y)
			{
				return false;
			}
		}
	}

	return true;
}

}