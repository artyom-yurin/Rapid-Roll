#pragma once

struct Collision
{
	bool collisionDown = false;
	bool collisionRight = false;
	bool collisionLeft = false;
};

Collision GetCollisions(sf::CircleShape & player, sf::RectangleShape(&platforms)[10]);