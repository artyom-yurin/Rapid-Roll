#include "stdafx.h"

struct Collision
{
	bool collisionDown = false;
	bool collisionRight = false;
	bool collisionLeft = false;
};

int GetRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> uniform_dist(min, max);
	return uniform_dist(engine);
}

sf::RectangleShape GeneratePlatform(sf::Vector2f & position, int & CountThorns)
{
	sf::RectangleShape platform;
	sf::Vector2f size = {100, 10};
	platform.setPosition(position);
	platform.setSize(size);
	if (CountThorns)
	{
		platform.setFillColor(sf::Color::Green);
		--CountThorns;
	}
	else
	{
		platform.setFillColor(sf::Color::Red);
		CountThorns = GetRandomNumber(1, 10);
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

Collision GetCollisions(sf::CircleShape & player, sf::RectangleShape(&platforms)[10])
{
	Collision currentCollision;
	for (sf::RectangleShape platform : platforms)
	{
		if ((platform.getGlobalBounds().left <= player.getGlobalBounds().left + player.getGlobalBounds().width / 2) &&
			(platform.getGlobalBounds().left + platform.getGlobalBounds().width >= player.getGlobalBounds().left + player.getGlobalBounds().width / 2) &&
			(platform.getGlobalBounds().top <= player.getGlobalBounds().top + player.getGlobalBounds().height) &&
			(platform.getGlobalBounds().top + platform.getGlobalBounds().height >= player.getGlobalBounds().top + player.getGlobalBounds().height)
			)
		{
			currentCollision.collisionDown = true;
		}

		if ((platform.getGlobalBounds().left <= player.getGlobalBounds().left + player.getGlobalBounds().width) &&
			(platform.getGlobalBounds().left >= player.getGlobalBounds().left + player.getGlobalBounds().width / 2) &&
			(((platform.getGlobalBounds().top >= player.getGlobalBounds().top) && (platform.getGlobalBounds().top + platform.getGlobalBounds().height <= player.getGlobalBounds().top + player.getGlobalBounds().height)) ||
			((platform.getGlobalBounds().top <= player.getGlobalBounds().top) && (platform.getGlobalBounds().top + platform.getGlobalBounds().height >= player.getGlobalBounds().top)) ||
			((platform.getGlobalBounds().top <= player.getGlobalBounds().top + player.getGlobalBounds().height) && (platform.getGlobalBounds().top + platform.getGlobalBounds().height >= player.getGlobalBounds().top + player.getGlobalBounds().height)))
			)
		{
			currentCollision.collisionRight = true;
		}

		if ((platform.getGlobalBounds().left + platform.getGlobalBounds().width >= player.getGlobalBounds().left) &&
			(platform.getGlobalBounds().left + platform.getGlobalBounds().width <= player.getGlobalBounds().left + player.getGlobalBounds().width / 2) &&
			(((platform.getGlobalBounds().top >= player.getGlobalBounds().top) && (platform.getGlobalBounds().top + platform.getGlobalBounds().height <= player.getGlobalBounds().top + player.getGlobalBounds().height)) ||
			((platform.getGlobalBounds().top <= player.getGlobalBounds().top) && (platform.getGlobalBounds().top + platform.getGlobalBounds().height >= player.getGlobalBounds().top)) ||
			((platform.getGlobalBounds().top <= player.getGlobalBounds().top + player.getGlobalBounds().height) && (platform.getGlobalBounds().top + platform.getGlobalBounds().height >= player.getGlobalBounds().top + player.getGlobalBounds().height)))
			)
		{
			currentCollision.collisionLeft = true;
		}
	}

	return currentCollision;
}

void InitPlayer(sf::CircleShape & player, sf::Vector2f position)
{
	player.setRadius(15);
	player.setFillColor(sf::Color::Red);
	player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
	position += {100 / 2, -(player.getGlobalBounds().height / 2)};
	player.setPosition(position);
}

void InitMap(sf::RectangleShape(&platforms)[10], int & CountThorns)
{
	CountThorns = GetRandomNumber(2, 10);
	for (int i = 0; i < 10; ++i)
	{
		sf::Vector2f position;
		position.x = (float)GetRandomNumber(0, 300); //TODO: Random value
		position.y = (float)100.0 * (i + 1); //TODO: I don't know
		platforms[i] = GeneratePlatform(position, CountThorns);
	}
}

void UpdatePlayer(sf::CircleShape & player, Collision & collisions, sf::Int64 & time)
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
	if (player.getPosition().y < 600 - player.getGlobalBounds().height / 2 && !collisions.collisionDown)
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
		InitPlayer(player, platforms[0].getPosition());
	}

	void Update(sf::Int64 time)
	{
		UpdatePlayer(player, GetCollisions(player, platforms), time);
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

