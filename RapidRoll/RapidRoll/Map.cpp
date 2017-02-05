#include "stdafx.h"
#include "RandomFunction.h"
#include "Map.h"
#include "Bonus.h"

sf::RectangleShape GeneratePlatform(sf::Vector2f & position, int & CountThorns, SBonus & bonus)
{
	sf::RectangleShape platform;
	sf::Vector2f size = { 100, 10 };
	platform.setPosition(position);
	platform.setSize(size);
	platform.setOrigin(platform.getGlobalBounds().width / 2, 0);
	if (CountThorns)
	{
		platform.setFillColor(sf::Color::Green);
		--CountThorns;
		if (bonus.countBonuses)
		{
			--bonus.countBonuses;
		}
		else
		{
			CreateNewBonus(bonus, platform);
			bonus.needDraw = true;
			bonus.countBonuses = 10/*GetRandomNumber(20, 60)*/;
		}
	}
	else
	{
		platform.setFillColor(sf::Color::Red);
		CountThorns = GetRandomNumber(1, 10);
	}
	return platform;
}

void InitMap(sf::RectangleShape(&platforms)[10], int & CountThorns, float & platformSpeed, SBonus & bonus)
{
	CountThorns = GetRandomNumber(2, 10);
	platformSpeed = -0.1f;
	sf::Vector2f position;
	position.x = (float)200;
	position.y = (float)300;
	platforms[0] = GeneratePlatform(position, CountThorns, bonus);
	for (int i = 1; i < 10; ++i)
	{
		position.x = platforms[i - 1].getPosition().x;
		if (position.x = 50)
		{
			position.x += (float)GetRandomNumber(50, 200);
		}
		else if (position.x = 350)
		{
			position.x += (float)GetRandomNumber(-200, -50);
		}
		else
		{
			position.x += (float)GetRandomNumber(-200, 200);
			if (position.x < 50)
			{
				position.x = 50;
			}
			else if (position.x > 350)
			{
				position.x = 350;
			}
		}
		position.y = (float)200 + 100 * (i + 1);
		platforms[i] = GeneratePlatform(position, CountThorns, bonus);
	}
}

void InitCeiling(sf::RectangleShape & ceiling)
{
	ceiling.setPosition(0, 30);
	sf::Vector2f ceilingSize = { 400, 30 };
	ceiling.setSize(ceilingSize);
	ceiling.setFillColor(sf::Color::Red);
}

void UpdateMap(sf::RectangleShape(&platforms)[10], sf::Int64 & time, float & platformSpeed, int & countThorns, SBonus & bonus)
{
	for (sf::RectangleShape & platform : platforms)
	{
		platform.move(0, platformSpeed * time);
	}
	if (platforms[1].getPosition().y < 15)
	{
		for (int i = 1; i < sizeof(platforms) / sizeof(*platforms); ++i)
		{
			platforms[i - 1] = platforms[i];
		}
		sf::Vector2f position;
		position.x = platforms[8].getPosition().x;
		if (position.x = 50)
		{
			position.x += (float)GetRandomNumber(50, 200);
		}
		else if (position.x = 350)
		{
			position.x += (float)GetRandomNumber(-200, -50);
		}
		else
		{
			position.x += (float)GetRandomNumber(-200, 200);
			if (position.x < 50)
			{
				position.x = 50;
			}
			else if (position.x > 350)
			{
				position.x = 350;
			}
		}
		position.y = (float)100 * 9;
		platforms[9] = GeneratePlatform(position, countThorns, bonus);
	}
}
