#pragma once

enum Status
{
	dead,
	live,
	bomb
};

struct SPlayer
{
	sf::CircleShape ball;
	int lives;
	float playerSpeed;
	int indexRespawn;
	Status status;
	sf::Int64 bonusTime;
	bool shield;
};

void ResetPlayer(SPlayer & player, sf::Vector2f position);

SPlayer InitPlayer(sf::Vector2f position);

void UpdatePlayer(SPlayer & player, sf::Int64 & time, float platformSpeed, sf::RectangleShape(&platforms)[10], struct SBonus & bonus);