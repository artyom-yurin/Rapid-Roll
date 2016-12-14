#pragma once

void InitPlayer(sf::CircleShape & player, sf::Vector2f position);

void UpdatePlayer(sf::CircleShape & player, sf::Int64 & time, float & platformSpeed, int & lives, sf::RectangleShape(&platforms)[10]);