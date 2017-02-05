#include "stdafx.h"
#include "Collision.h"

Collision GetCollisionsPlayer(sf::CircleShape & player, sf::RectangleShape(&platforms)[10])
{
	Collision currentCollision;
	int i = 0;
	for (sf::RectangleShape platform : platforms)
	{
		if ((platform.getGlobalBounds().left <= player.getGlobalBounds().left + player.getGlobalBounds().width / 2) &&
			(platform.getGlobalBounds().left + platform.getGlobalBounds().width >= player.getGlobalBounds().left + player.getGlobalBounds().width / 2) &&
			(platform.getGlobalBounds().top <= player.getGlobalBounds().top + player.getGlobalBounds().height) &&
			(platform.getGlobalBounds().top + platform.getGlobalBounds().height >= player.getGlobalBounds().top + player.getGlobalBounds().height)
			)
		{
			currentCollision.collisionDown = true;
			currentCollision.platformIndex = i;
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
		if (player.getGlobalBounds().top < 60 || player.getGlobalBounds().top > 600)
		{
			currentCollision.collisionExtreme = true;
		}
		++i;
	}

	return currentCollision;
}

Collision GetCollisionsBonus(sf::RectangleShape & bonus, sf::RectangleShape(&platforms)[10])
{
	Collision currentCollision;

	int i = 0;
	for (sf::RectangleShape platform : platforms)
	{
		if ((platform.getGlobalBounds().left <= bonus.getGlobalBounds().left + bonus.getGlobalBounds().width / 2) &&
			(platform.getGlobalBounds().left + platform.getGlobalBounds().width >= bonus.getGlobalBounds().left + bonus.getGlobalBounds().width / 2) &&
			(platform.getGlobalBounds().top <= bonus.getGlobalBounds().top + bonus.getGlobalBounds().height) &&
			(platform.getGlobalBounds().top + platform.getGlobalBounds().height >= bonus.getGlobalBounds().top + bonus.getGlobalBounds().height)
			)
		{
			currentCollision.collisionDown = true;
			currentCollision.platformIndex = i;
		}
		++i;
	}

	return currentCollision;
}

bool CollisionWithBonus(const sf::CircleShape & player, const sf::RectangleShape & bonus)
{
	float x11 = player.getGlobalBounds().left;
	float y11 = player.getGlobalBounds().top;
	float x12 = x11 + player.getGlobalBounds().width;
	float y12 = y11 + player.getGlobalBounds().height;

	float x21 = bonus.getGlobalBounds().left;
	float y21 = bonus.getGlobalBounds().top;
	float x22 = x21 + bonus.getGlobalBounds().width;
	float y22 = y21 + bonus.getGlobalBounds().height;

	if ((x11 <= x22 && x11 >= x21) || (x12 <= x22 && x12 >= x21))
	{
		if ((y11 <= y22 && y11 >= y21) || (y12 <= y22 && y12 >= y21))
		{
			return true;
		}
	}
	else if ((x21 <= x12 && x21 >= x11) || (x22 <= x12 && x22 >= x11))
	{
		if ((y21 <= y12 && y21 >= y11) || (y22 <= y12 && y22 >= y11))
		{
			return true;
		}
	}

	return false;
}
