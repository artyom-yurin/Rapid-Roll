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
	float score;
	float playerSpeed;
	int indexRespawn;
	bool isBig;
	Status status;
	sf::Int64 bonusTime;
	bool shield;
};

void ResetPlayer(SPlayer & player, sf::Vector2f position);

SPlayer InitPlayer(sf::Vector2f position);

void UpdatePlayer(SPlayer & player, sf::Int64 & time, float & platformSpeed, struct SPlatform(&platforms)[10], struct SBonus & bonus, sf::Sprite const & ceiling);