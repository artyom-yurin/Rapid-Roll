#pragma once

void UpdateMap(sf::RectangleShape(&platforms)[10], sf::Int64 & time, float & platformSpeed, int & countThorns, struct SBonus & bonus);

void InitMap(sf::RectangleShape(&platforms)[10], int & CountThorns, float & platformSpeed, struct SBonus & bonus);

void InitCeiling(sf::RectangleShape & ceiling);