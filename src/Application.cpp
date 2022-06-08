#include "Application.h"
#include "ResourceManager.h"

#include <cstdio>

namespace nadpher
{
sf::RenderWindow Application::window_;
Board Application::board_;

bool Application::init(unsigned int width, unsigned int height, const char* title)
{
	window_.create(sf::VideoMode(width, height), title);

	if (!window_.isOpen())
	{
		printf("Couldn't create SFML window\n");
		return false;
	}

	return true;
}

void Application::run()
{
	while (window_.isOpen())
	{
		handleEvents();

		window_.clear();

		drawBoard();

		window_.display();
	}
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
				num.setPosition(sf::Vector2f(cellSizeX * j, cellSizeY * i));

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
		arr[0].position = sf::Vector2f(cellSizeX * i, 0);
		arr[1].position = sf::Vector2f(cellSizeX * i, realBoardSizeY);

		window_.draw(arr);

		// rows
		arr[0].position = sf::Vector2f(0, cellSizeY * i);
		arr[1].position = sf::Vector2f(realBoardSizeX, cellSizeY * i);

		window_.draw(arr);
	}
}

void Application::handleEvents()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window_.close();
			break;

		default:
			break;
		}
	}
}

}