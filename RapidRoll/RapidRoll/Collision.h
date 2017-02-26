#pragma once

struct Collision
{
	bool collisionExtreme = false;
	bool collisionDown = false;
	bool collisionRight = false;
	bool collisionLeft = false;
	int platformIndex = -1;
};

Collision GetCollisionsPlayer(sf::CircleShape & player, struct SPlatform(&plastforms)[10], sf::Sprite const & ceiling);

Collision GetCollisionsBonus(sf::Sprite & bonus, struct SPlatform(&plastforms)[10]);

bool CollisionWithBonus(const sf::CircleShape & player, const sf::Sprite & bonus);