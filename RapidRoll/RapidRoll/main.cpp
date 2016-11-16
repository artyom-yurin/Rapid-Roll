#include "stdafx.h"

sf::RectangleShape GeneratePlatform(sf::Vector2f & position, int & CountThorns)
{
	sf::RectangleShape platform;
	sf::Vector2f size = {100, 10};
	platform.setPosition(position);
	platform.setSize(size);
	platform.setOrigin(platform.getGlobalBounds().width / 2, platform.getGlobalBounds().height / 2);
	if (CountThorns)
	{
		platform.setFillColor(sf::Color::Green);
		--CountThorns;
	}
	else
	{
		platform.setFillColor(sf::Color::Red);
		CountThorns = 4; //TODO: Random value
	}
	return platform;
}

void UpdateMap(sf::RectangleShape (&platforms)[10], sf::Int64 & time)
{

}

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

void InitMap(sf::RectangleShape(&platforms)[10], int & CountThorns)
{
	CountThorns = 4;
	for (int i = 0; i < 10; ++i)
	{
		sf::Vector2f position;
		position.x = 100.0; //TODO: Random value
		position.y = (float)100.0 * (i + 1); //TODO: I don't know
		platforms[i] = GeneratePlatform(position, CountThorns);
	}
}

bool GetCollisionUp(sf::CircleShape & player, sf::RectangleShape (&platforms)[10])
{
	for (sf::RectangleShape platform : platforms)
	{
		if ((platform.getGlobalBounds().left <= player.getGlobalBounds().left + player.getGlobalBounds().width / 2) &&
			(platform.getGlobalBounds().left + platform.getGlobalBounds().width >= player.getGlobalBounds().left + player.getGlobalBounds().width / 2) &&
			(platform.getGlobalBounds().top <= player.getGlobalBounds().top + player.getGlobalBounds().height) &&
			(platform.getGlobalBounds().top + platform.getGlobalBounds().height >= player.getGlobalBounds().top + player.getGlobalBounds().height)
			)
		{
			return true;
		}
	}

	return false;
}

void UpdatePlayer(sf::CircleShape & player, bool hasCollision, sf::Int64 & time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { 
		if (player.getPosition().x > 0 + player.getGlobalBounds().width / 2)
		{
			player.move(-0.1f * time, 0);
		}
	};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
		if (player.getPosition().x < 400 - player.getGlobalBounds().width / 2)
		{
			player.move(0.1f * time, 0);
		}
	};
	if (player.getPosition().y < 600 - player.getGlobalBounds().height / 2 && !hasCollision)
	{
		player.move(0, 0.1f * time);
	}
}

struct Application
{
	sf::RenderWindow window;
	sf::CircleShape player;
	int CountThorns;
	sf::RectangleShape platforms[10];
	sf::Event event;

	void InitApplication()
	{
		InitWindow(window);
		InitMap(platforms, CountThorns);
		InitPlayer(player);
	}

	void Update(sf::Int64 time)
	{
		UpdatePlayer(player, GetCollisionUp(player, platforms), time);
		UpdateMap(platforms, time);
	}

	void Draw()
	{
		for (sf::RectangleShape platform : platforms)
		{
			window.draw(platform);
		}
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

	sf::Clock clock;
	while (app.window.isOpen())
	{
		sf::Int64 time = clock.getElapsedTime().asMicroseconds();
		clock.restart(); 
		time = time / 600;

		app.HandleEvents();

		app.Update(time);

		app.window.clear(sf::Color::White);

		app.Draw();

		app.window.display();
	}

    return 0;
}

