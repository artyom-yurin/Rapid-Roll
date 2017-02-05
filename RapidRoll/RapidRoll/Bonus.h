#pragma once

struct SBonus
{
	sf::RectangleShape bonus;
	int BonusType;
	int countBonuses;
	bool needDraw;
};

SBonus InitBonus();

void UpdateBonus(SBonus & bonus, sf::Int64 & time, float platformSpeed, sf::RectangleShape(&platforms)[10]);

void CreateNewBonus(SBonus & bonus, const sf::RectangleShape & platform);
