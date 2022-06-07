#pragma once

#include "Board.h"

#include <SFML/Graphics.hpp>

namespace nadpher
{

class Application
{
public:

	static bool init(unsigned int width, unsigned int height, const char* title = "Sudoku");
	static void run();

	static constexpr unsigned int realBoardSizeX = 500;
	static constexpr unsigned int realBoardSizeY = 500 ;

private:
	static void handleEvents();
	static void drawBoard();

	static sf::RenderWindow window_;
	static Board board_;
};

}


