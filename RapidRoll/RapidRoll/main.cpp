#include "stdafx.h"

void InitWindow(sf::RenderWindow & window)
{
	const int screenWidth = 400;
	const int screenHeight = 600;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(screenWidth, screenHeight), "Rapid Roll", sf::Style::Close, settings);
}

void InitPlayer(sf::CircleShape & player)
{
	player.setRadius(15);
	player.setFillColor(sf::Color::Red);
	player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
	player.setPosition({100, 50});
}

void UpdatePlayer(sf::CircleShape & player)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { 
		if (player.getPosition().x > 0 + player.getGlobalBounds().width / 2)
		{
			player.move(-0.1f, 0);
		}
	};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
		if (player.getPosition().x < 400 - player.getGlobalBounds().width / 2)
		{
			player.move(0.1f, 0);
		}
	};
	if (player.getPosition().y < 600 - player.getGlobalBounds().height / 2)
	{
		player.move(0, 0.1f);
	}
}

struct Application
{
	sf::RenderWindow window;
	sf::CircleShape player;
	sf::Event event;

	void InitApplication()
	{
		InitWindow(window);
		InitPlayer(player);
	}

	void Update()
	{
		UpdatePlayer(player);
	}

	void Draw()
	{
		window.draw(player);
	}

	void HandleEvents()
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
};

int main()
{
	Application app;

	app.InitApplication();

	while (app.window.isOpen())
	{
		app.HandleEvents();

		app.Update();

		app.window.clear(sf::Color::White);

		app.Draw();

		app.window.display();
	}

    return 0;
}

