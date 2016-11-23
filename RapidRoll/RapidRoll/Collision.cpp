#include "stdafx.h"
#include "Collision.h"

Collision GetCollisions(sf::CircleShape & player, sf::RectangleShape(&platforms)[10])
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
		if (player.getGlobalBounds().top < 30 || player.getGlobalBounds().top > 600)
		{
			currentCollision.collisionExtreme = true;
		}
		++i;
	}

	return currentCollision;
}
