#pragma once

#include "Board.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>

namespace nadpher
{

class Application
{
public:

	static bool init(unsigned int width, unsigned int height, const char* title = "Sudoku");
	static void run();

	static constexpr unsigned int realBoardPositionX = 200;
	static constexpr unsigned int realBoardPositionY = 200;
	static constexpr unsigned int realBoardSizeX = 400;
	static constexpr unsigned int realBoardSizeY = 400;

private:
	static void handleEvents();
	static void drawBoard();
	static void drawBounds();
	static void drawNumbers();

	static unsigned int selected_;

	static sf::RenderWindow window_;
	static Board board_;
	static tgui::Gui gui_;
};

}


