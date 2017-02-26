#pragma once

struct SBonus
{
	sf::Sprite bonus;
	int BonusType;
	int countBonuses;
	bool needDraw;
};

SBonus InitBonus(sf::Texture const & texture);

void UpdateBonus(SBonus & bonus, sf::Int64 & time, float platformSpeed, struct SPlatform(&platforms)[10]);

void CreateNewBonus(SBonus & bonus, const sf::Sprite & platform);
