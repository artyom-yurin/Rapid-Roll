#include "stdafx.h"
#include "Map.h"

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
	sf::Vector2f size = { 100, 10 };
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

void InitMap(sf::RectangleShape(&platforms)[10], int & CountThorns, float & platformSpeed, sf::RectangleShape & ceiling)
{
	CountThorns = GetRandomNumber(2, 10);
	ceiling.setPosition(0, 0);
	sf::Vector2f ceilingSize = {400, 30};
	ceiling.setSize(ceilingSize);
	ceiling.setFillColor(sf::Color::Red);
	platformSpeed = -0.1f;
	for (int i = 0; i < 10; ++i)
	{
		sf::Vector2f position;
		position.x = (float)GetRandomNumber(0, 300); //TODO: Random value
		position.y = (float)200 + 100 * (i + 1);
		platforms[i] = GeneratePlatform(position, CountThorns);
	}
}

void UpdateMap(sf::RectangleShape(&platforms)[10], sf::Int64 & time, float & platformSpeed, int & countThorns)
{
	for (sf::RectangleShape & platform : platforms)
	{
		platform.move(0, platformSpeed * time);
	}
	if (platforms[1].getPosition().y < 0)
	{
		for (int i = 1; i < sizeof(platforms) / sizeof(*platforms); ++i)
		{
			platforms[i - 1] = platforms[i];
		}
		sf::Vector2f position;
		position.x = (float)GetRandomNumber(0, 300);
		position.y = (float)100 * 9;
		platforms[9] = GeneratePlatform(position, countThorns);
	}
}