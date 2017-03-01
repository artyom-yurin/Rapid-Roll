#include "stdafx.h"
#include "Collision.h"
#include "RandomFunction.h"
#include "Map.h"
#include "Bonus.h"

SBonus InitBonus(sf::Texture const & texture)
{
	SBonus currentBonus;
	currentBonus.bonus.setTexture(texture);
	currentBonus.bonus.setOrigin(currentBonus.bonus.getGlobalBounds().width / 2, currentBonus.bonus.getGlobalBounds().height / 2);
	currentBonus.bonus.setPosition(0, 0);
	currentBonus.countBonuses = GetRandomNumber(20, 60);
	currentBonus.needDraw = false;
	return currentBonus;
}

void UpdateBonus(SBonus & bonus, sf::Int64 & time, float platformSpeed, SPlatform(&platforms)[10])
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

SBonus CreateNewBonus(const sf::Sprite & platform, const sf::Texture & texture)
{
	SBonus bonus = InitBonus(texture);
	bonus.BonusType = GetRandomNumber(1, 3);
	if (bonus.BonusType == 1)
	{
		bonus.bonus.setTextureRect(sf::IntRect(2, 276, 123, 141));
	}
	else if (bonus.BonusType == 2)
	{
		bonus.bonus.setTextureRect(sf::IntRect(125, 277, 123, 134));
	}
	else if (bonus.BonusType == 3)
	{
		bonus.bonus.setTextureRect(sf::IntRect(254, 277, 130, 130));
	}
	bonus.bonus.setOrigin(bonus.bonus.getGlobalBounds().width / 2, bonus.bonus.getGlobalBounds().height / 2);
	bonus.bonus.scale(0.25, 0.25);
	bonus.bonus.setPosition((float)GetRandomNumber((int)(platform.getGlobalBounds().left + bonus.bonus.getGlobalBounds().width / 2), (int)(platform.getGlobalBounds().left + platform.getGlobalBounds().width - bonus.bonus.getGlobalBounds().width / 2)), platform.getPosition().y - (bonus.bonus.getGlobalBounds().height / 2));
	return bonus;
}
