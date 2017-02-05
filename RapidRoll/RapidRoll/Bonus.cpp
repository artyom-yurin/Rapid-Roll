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
	if (bonus.bonus.getPosition().y < 0)
	{
		bonus.needDraw = false;
	}
}

void CreateNewBonus(SBonus & bonus, const sf::RectangleShape & platform)
{
	bonus.BonusType = 3/*GetRandomNumber(1, 3)*/;
	bonus.bonus.setPosition((float)GetRandomNumber((int)platform.getGlobalBounds().left, (int)(platform.getGlobalBounds().left + platform.getGlobalBounds().width - bonus.bonus.getGlobalBounds().width / 2)), platform.getPosition().y - (bonus.bonus.getGlobalBounds().height / 2));
	if (bonus.BonusType == 1)
	{
		// TODO: Big ball
	}
	else if (bonus.BonusType == 2)
	{
		// TODO: Shield
	}
	else
	{
		bonus.bonus.setFillColor(sf::Color::Magenta);
	}
}
