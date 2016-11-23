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
	position += {0, -(player.getGlobalBounds().height / 2)};
	player.setPosition(position);
}

void UpdatePlayer(sf::CircleShape & player, sf::Int64 & time, float & platformSpeed, int & lives, sf::RectangleShape(&platforms)[10])
{
	Collision collisions = GetCollisions(player, platforms);

	if (collisions.platformIndex != -1)
	{
		if (platforms[collisions.platformIndex].getFillColor() == sf::Color::Red)
		{
			--lives;
			int startIndexPlatform = collisions.platformIndex;
			if (startIndexPlatform + 1 == 10)
			{
				startIndexPlatform -= 1;
			}
			else
			{
				startIndexPlatform += 1;
			}
			InitPlayer(player, platforms[startIndexPlatform].getPosition());
		}
	}

	if (collisions.collisionExtreme)
	{
		--lives;
		int startIndexPlatform = -1;
		int i = 0;
		while (startIndexPlatform == -1)
		{
			if (platforms[i].getGlobalBounds().top > 200 && platforms[i].getFillColor() != sf::Color::Red)
			{
				startIndexPlatform = i;
			}
			++i;
		}
		InitPlayer(player, platforms[startIndexPlatform].getPosition());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
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
	else
	{
		player.move(0, 0.1f * time);
	}
}

struct Application
{
	sf::RenderWindow window;
	sf::CircleShape player;
	int countThorns;
	int lives = 3;
	float platformSpeed;
	sf::RectangleShape platforms[10];
	sf::RectangleShape ceiling;
	sf::Event event;

	void InitApplication()
	{
		InitWindow(window);
		InitMap(platforms, countThorns, platformSpeed, ceiling);
		InitPlayer(player, platforms[0].getPosition());
	}

	void Update(sf::Int64 time)
	{
		UpdatePlayer(player, time, platformSpeed, lives, platforms);
		UpdateMap(platforms, time, platformSpeed, countThorns);
	}

	void Draw()
	{
		for (sf::RectangleShape platform : platforms)
		{
			window.draw(platform);
		}
		window.draw(ceiling);
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
		app.HandleEvents();

		if (app.lives)
		{
			sf::Int64 time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 600;

			app.Update(time);
		}

		app.window.clear(sf::Color::White);

		app.Draw();

		app.window.display();
	}

    return 0;
}

