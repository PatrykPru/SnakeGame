#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
	srand(time(0));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(500, 500), "Snake 3.0", sf::Style::Titlebar | sf::Style::Close, settings);
	Game game(window);
	window->setFramerateLimit(120);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		game.update();
		game.display();

	}

	return 0;
}