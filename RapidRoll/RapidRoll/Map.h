#pragma once

struct SPlatform
{
	sf::Sprite platform;
	bool isThorn = false;
};

void UpdateMap(struct SPlatform (&platforms)[10], sf::Int64 & time, float & platformSpeed, int & countThorns, struct SBonus & bonus, sf::Texture const & texture);

void InitMap(struct SPlatform (&platforms)[10], int & CountThorns, float & platformSpeed, struct SBonus & bonus, sf::Texture const & texture);

void InitCeiling(sf::Sprite & ceiling, sf::Texture const & texture);