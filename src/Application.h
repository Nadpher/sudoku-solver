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

	bool init(unsigned int width, unsigned int height, const char* title = "Sudoku");
	void run();

	static constexpr unsigned int realBoardPositionX = 200;
	static constexpr unsigned int realBoardPositionY = 200;
	static constexpr unsigned int realBoardSizeX = 400;
	static constexpr unsigned int realBoardSizeY = 400;

private:
	void handleEvents();
	void handleMousePress(const sf::Event& event);

	void drawBoard();
	void drawBounds();
	void drawNumbers();

	void solve();

	unsigned int value_ = 0;

	sf::RenderWindow window_;
	Board board_;
	tgui::Gui gui_;
};

}


