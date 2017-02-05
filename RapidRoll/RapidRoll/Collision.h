#pragma once

struct Collision
{
	bool collisionExtreme = false;
	bool collisionDown = false;
	bool collisionRight = false;
	bool collisionLeft = false;
	int platformIndex = -1;
};

Collision GetCollisionsPlayer(sf::CircleShape & player, sf::RectangleShape(&plastforms)[10]);

Collision GetCollisionsBonus(sf::RectangleShape & bonus, sf::RectangleShape(&plastforms)[10]);

bool CollisionWithBonus(const sf::CircleShape & player, const sf::RectangleShape & bonus);