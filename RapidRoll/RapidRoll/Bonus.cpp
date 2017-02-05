#include "stdafx.h"
#include "Collision.h"
#include "RandomFunction.h"
#include "Bonus.h"

SBonus InitBonus()
{
	SBonus currentBonus;
	sf::Vector2f size(20, 20);
	currentBonus.bonus.setSize(size);
	currentBonus.bonus.setOrigin(currentBonus.bonus.getGlobalBounds().width / 2, currentBonus.bonus.getGlobalBounds().height / 2);
	currentBonus.countBonuses = GetRandomNumber(20, 60);
	currentBonus.needDraw = false;
	return currentBonus;
}

void UpdateBonus(SBonus & bonus, sf::Int64 & time, float platformSpeed, sf::RectangleShape(&platforms)[10])
{
	Collision collisions = GetCollisionsBonus(bonus.bonus, platforms);
	if (collisions.collisionDown)
	{
		bonus.bonus.move(0, platformSpeed * time);
	}
	if (bonus.bonus.getPosition().y + bonus.bonus.getGlobalBounds().height < 0)
	{
		bonus.needDraw = false;
	}
}

void CreateNewBonus(sf::RectangleShape & bonus, const sf::RectangleShape & platform)
{
	int typeBonus = GetRandomNumber(1, 3);
	bonus.setPosition((float)GetRandomNumber((int)platform.getPosition().x, (int)(platform.getPosition().x + platform.getGlobalBounds().width)), platform.getPosition().y - (bonus.getGlobalBounds().height / 2));
	if (/*typeBonus == 1*/false)
	{
		// TODO: Big ball
	}
	else if (/*typeBonus == 2*/false)
	{
		// TODO: Shield
	}
	else
	{
		bonus.setFillColor(sf::Color::Magenta);
	}
}
