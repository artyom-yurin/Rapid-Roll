#include "stdafx.h"
#include "Collision.h"
#include "Map.h"

void InitWindow(sf::RenderWindow & window)
{
	const int screenWidth = 400;
	const int screenHeight = 600;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(screenWidth, screenHeight), "Rapid Roll", sf::Style::Close, settings);
}

void InitPlayer(sf::CircleShape & player, sf::Vector2f position)
{
	player.setRadius(15);
	player.setFillColor(sf::Color::Red);
	player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
	position += {100 / 2, -(player.getGlobalBounds().height / 2)};
	player.setPosition(position);
}

void UpdatePlayer(sf::CircleShape & player, Collision & collisions, sf::Int64 & time, float & platformSpeed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { 
		if (player.getPosition().x > player.getGlobalBounds().width / 2 && !collisions.collisionLeft)
		{
			player.move(-0.1f * time, 0);
		}
	};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
		if (player.getPosition().x < 400 - player.getGlobalBounds().width / 2 && !collisions.collisionRight)
		{
			player.move(0.1f * time, 0);
		}
	};
	if (collisions.collisionDown)
	{
		player.move(0, platformSpeed * time);
	}
	else if (player.getPosition().y < 600 - player.getGlobalBounds().height / 2)
	{
		player.move(0, 0.1f * time);
	}
}

struct Application
{
	sf::RenderWindow window;
	sf::CircleShape player;
	int countThorns;
	float platformSpeed;
	sf::RectangleShape platforms[10];
	sf::Event event;

	void InitApplication()
	{
		InitWindow(window);
		InitMap(platforms, countThorns, platformSpeed);
		InitPlayer(player, platforms[0].getPosition());
	}

	void Update(sf::Int64 time)
	{
		UpdatePlayer(player, GetCollisions(player, platforms), time, platformSpeed);
		UpdateMap(platforms, time, platformSpeed, countThorns);
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

