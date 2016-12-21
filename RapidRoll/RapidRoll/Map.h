#pragma once

void UpdateMap(sf::RectangleShape(&platforms)[10], sf::Int64 & time, float & platformSpeed, int & countThorns);

void InitMap(sf::RectangleShape(&platforms)[10], int & CountThorns, float & platformSpeed);

void InitCeiling(sf::RectangleShape & ceiling);