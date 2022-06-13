#include "Application.h"
#include "ResourceManager.h"
#include "Solver.h"

#include <cstdio>
#include <string>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/Label.hpp>

namespace nadpher
{

bool Application::init(unsigned int width, unsigned int height, const char* title)
{
	window_.create(sf::VideoMode(width, height), title);

	if (!window_.isOpen())
	{
		printf("Couldn't create SFML window\n");
		return false;
	}

	gui_.setTarget(window_);

	return true;
}

void Application::run()
{
	tgui::Label::Ptr label = tgui::Label::create("Selected number: " + std::to_string(value_));
	gui_.add(label, "label");
	label->setTextSize(24);
	label->setOrigin(0.0f, 1.0f);
	label->setPosition("0", "100%");

	for (unsigned int i = 1; i <= Board::boardLength; ++i)
	{
		std::string id = std::to_string(i);

		tgui::Button::Ptr button = tgui::Button::create(id);
		gui_.add(button, id);
		// when button is pressed, corresponding number is assigned to value
		// and the label is changed to match the right value
		button->onPress([=](unsigned int x) { value_ = x; label->setText("Selected number: " + std::to_string(x)); }, i);

		// temporary positioning
		button->setPosition((i - 1) * 50, 0);
	}

	tgui::Button::Ptr solver = tgui::Button::create("solve");
	gui_.add(solver, "solver");
	solver->onPress(&Application::solve, this);
	solver->setPosition("100%", "0%");
	solver->setOrigin(1.0f, 0.0f);

	tgui::Button::Ptr clear = tgui::Button::create("clear");
	gui_.add(clear, "clear");
	clear->onPress([&] {board_.clear(); });
	clear->setOrigin(1.0f, 0.0f);
	clear->setPosition("100%", "solver.bottom + 20");

	while (window_.isOpen())
	{
		handleEvents();

		window_.clear();

		drawBoard();
		gui_.draw();

		window_.display();
	}
}

void Application::solve()
{
	Solver solver(board_);
	solver.solve();
}

void Application::drawBoard()
{
	drawBounds();
	drawNumbers();
}

void Application::drawNumbers()
{
	float cellSizeX = realBoardSizeX / static_cast<float>(Board::boardLength);
	float cellSizeY = realBoardSizeY / static_cast<float>(Board::boardLength);

	for (unsigned int i = 0; i < Board::boardLength; ++i)
	{
		for (unsigned int j = 0; j < Board::boardLength; ++j)
		{
			unsigned int value = board_.readCell({j, i});

			if (value)
			{
				sf::Text num;
				num.setString(std::to_string(value));
				num.setFont(*ResourceManager<sf::Font>::get("res/arial.ttf"));
				num.setPosition(sf::Vector2f(cellSizeX * j + realBoardPositionX, cellSizeY * i + realBoardPositionY));

				window_.draw(num);
			}
		}
	}
}

void Application::drawBounds()
{
	float cellSizeX = realBoardSizeX / static_cast<float>(Board::boardLength);
	float cellSizeY = realBoardSizeY / static_cast<float>(Board::boardLength);

	sf::VertexArray arr(sf::LineStrip, 2);

	const sf::Color grey(50, 50, 50, 255);

	for (int i = 0; i <= Board::boardLength; ++i)
	{
		arr[0].color = grey;
		arr[1].color = grey;

		if (i % 3 == 0)
		{
			arr[0].color = sf::Color::White;
			arr[1].color = sf::Color::White;
		}

		// columns
		arr[0].position = sf::Vector2f(cellSizeX * i + realBoardPositionX, realBoardPositionY);
		arr[1].position = sf::Vector2f(cellSizeX * i + realBoardPositionX, realBoardSizeY + realBoardPositionY);

		window_.draw(arr);

		// rows
		arr[0].position = sf::Vector2f(realBoardPositionX, cellSizeY * i + realBoardPositionY);
		arr[1].position = sf::Vector2f(realBoardSizeX + realBoardPositionX, cellSizeY * i + realBoardPositionY);

		window_.draw(arr);
	}
}

void Application::handleEvents()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		gui_.handleEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			window_.close();
			break;

		case sf::Event::MouseButtonPressed:
			handleMousePress(event);
			break;

		default:
			break;
		}
	}
}

void Application::handleMousePress(const sf::Event& event)
{
	// place
	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		// if clicked inside sudoku board
		if (event.mouseButton.x > realBoardPositionX &&
			event.mouseButton.x < realBoardPositionX + realBoardSizeX &&
			event.mouseButton.y > realBoardPositionY &&
			event.mouseButton.y < realBoardPositionY + realBoardSizeY)
		{
			float cellSizeX = realBoardSizeX / static_cast<float>(Board::boardLength);
			float cellSizeY = realBoardSizeY / static_cast<float>(Board::boardLength);

			// converts mouse position to board cell
			// implicit rounding
			Coord pos = { event.mouseButton.x - realBoardPositionX, event.mouseButton.y - realBoardPositionY };
			pos.x /= cellSizeX;
			pos.y /= cellSizeY;

			if (!board_.readCell(pos))
			{
				board_.setCell(value_, pos);

				// prevents user from entering invalid number
				// to keep board solvable
				if (!board_.checkCell(pos))
				{
					board_.setCell(0, pos);
				}
			}
		}
	}
	// erase
	else if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		// if clicked inside sudoku board
		if (event.mouseButton.x > realBoardPositionX &&
			event.mouseButton.x < realBoardPositionX + realBoardSizeX &&
			event.mouseButton.y > realBoardPositionY &&
			event.mouseButton.y < realBoardPositionY + realBoardSizeY)
		{
			float cellSizeX = realBoardSizeX / static_cast<float>(Board::boardLength);
			float cellSizeY = realBoardSizeY / static_cast<float>(Board::boardLength);

			// converts mouse position to board cell
			// implicit rounding
			Coord pos = { event.mouseButton.x - realBoardPositionX, event.mouseButton.y - realBoardPositionY };
			pos.x /= cellSizeX;
			pos.y /= cellSizeY;

			board_.setCell(0, pos);
		}
	}
}

}