#pragma once

struct Collision
{
	bool collisionExtreme = false;
	bool collisionDown = false;
	bool collisionRight = false;
	bool collisionLeft = false;
	int platformIndex = -1;
};

Collision GetCollisions(sf::CircleShape & player, sf::RectangleShape(&plastforms)[10]);