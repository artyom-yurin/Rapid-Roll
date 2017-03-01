#include "stdafx.h"
#include "RandomFunction.h"
#include "Map.h"
#include "Bonus.h"

SPlatform GeneratePlatform(sf::Vector2f & position, int & CountThorns, SBonus & bonus, sf::Texture const & texture)
{
	SPlatform platform;
	platform.platform.setTexture(texture);
	if (CountThorns)
	{
		platform.platform.setTextureRect(sf::IntRect(0, 0, 497, 115));
		platform.isThorn = false;
		--CountThorns;
	}
	else
	{
		platform.platform.setTextureRect(sf::IntRect(2, 119, 469, 158));
		platform.isThorn = true;
		CountThorns = GetRandomNumber(1, 10);
	}
	platform.platform.setOrigin(platform.platform.getGlobalBounds().width / 2, 0);
	platform.platform.setScale(0.25, 0.25);
	platform.platform.setPosition(position);
	if (!platform.isThorn)
	{
		if (bonus.countBonuses)
		{
			--bonus.countBonuses;
		}
		else
		{
			bonus = CreateNewBonus(platform.platform, texture);
			bonus.needDraw = true;
			bonus.countBonuses = GetRandomNumber(20, 60);
		}
	}
	return platform;
}

void InitMap(SPlatform(&platforms)[10], int & CountThorns, float & platformSpeed, SBonus & bonus, sf::Texture const & texture)
{
	CountThorns = GetRandomNumber(2, 10);
	platformSpeed = -0.1f;
	sf::Vector2f position;
	position.x = (float)200;
	position.y = (float)300;
	platforms[0] = GeneratePlatform(position, CountThorns, bonus, texture);
	for (int i = 1; i < 10; ++i)
	{
		position.x = platforms[i - 1].platform.getPosition().x;
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
		platforms[i] = GeneratePlatform(position, CountThorns, bonus, texture);
	}
}

void InitCeiling(sf::Sprite & ceiling, sf::Texture const & texture)
{
	ceiling.setTexture(texture);
	ceiling.setTextureRect(sf::IntRect(0, 425, 1544, 80));
	ceiling.setScale(0.25, 0.25);
	ceiling.setPosition(6, 30);
}

void UpdateMap(SPlatform(&platforms)[10], sf::Int64 & time, float & platformSpeed, int & countThorns, SBonus & bonus, sf::Texture const & texture)
{
	for (SPlatform & platform : platforms)
	{
		platform.platform.move(0, platformSpeed * time);
	}
	if (platforms[1].platform.getPosition().y < 15)
	{
		for (int i = 1; i < sizeof(platforms) / sizeof(*platforms); ++i)
		{
			platforms[i - 1] = platforms[i];
		}
		sf::Vector2f position;
		position.x = platforms[8].platform.getPosition().x;
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
		platforms[9] = GeneratePlatform(position, countThorns, bonus, texture);
	}
}
