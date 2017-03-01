#include "stdafx.h"
#include "Speed.h"
#include "Bonus.h"
#include "Collision.h"
#include "Player.h"
#include "Map.h"

void ResetPlayer(SPlayer & player, sf::Vector2f position)
{
	player.ball.setRadius(15);
	player.ball.setOrigin(player.ball.getGlobalBounds().width / 2, player.ball.getGlobalBounds().height / 2);
	player.ball.setFillColor(sf::Color::Red);
	player.status = Status::live;
	position += {0, -(player.ball.getGlobalBounds().height / 2)};
	player.ball.setPosition(position);
	float speed = player.playerSpeed / 100000;
	player.playerSpeed = std::max(0.1f, speed);
	player.playerSpeed = std::min(0.3f, player.playerSpeed);
	player.shield = false;
	player.isBig = false;
	player.bonusTime = 0;
}

SPlayer InitPlayer(sf::Vector2f position)
{
	SPlayer player;
	player.status = Status::live;
	player.lives = 3;
	player.score = 0;
	player.isBig = false;
	player.playerSpeed = 0.1f;
	player.ball.setRadius(15);
	player.ball.setFillColor(sf::Color::Red);
	player.ball.setOrigin(player.ball.getGlobalBounds().width / 2, player.ball.getGlobalBounds().height / 2);
	position += {0, -(player.ball.getGlobalBounds().height / 2)};
	player.ball.setPosition(position);
	return player;
}

void UpdatePlayer(SPlayer & player, sf::Int64 & time, float & platformSpeed, SPlatform(&platforms)[10], SBonus & bonus, sf::Sprite const & ceiling)
{
	if (player.status == Status::dead)
	{
		player.indexRespawn = -1;
		int i = 0;
		for (SPlatform platform: platforms)
		{
			if (platform.platform.getGlobalBounds().top > 300 && platform.platform.getGlobalBounds().top < 400 && !platform.isThorn)
			{
				player.indexRespawn = i;
			}
			++i;
		}
		if (player.indexRespawn != -1)
		{
			ResetPlayer(player, platforms[player.indexRespawn].platform.getPosition());
		}
	}
	else
	{
		if (CollisionWithBonus(player.ball, bonus.bonus))
		{
			bonus.needDraw = false;
			bonus.bonus.setPosition(0, 0);
			if (bonus.BonusType == 1)
			{
				player.shield = true;
				player.bonusTime = 30000; 
				player.ball.setFillColor(sf::Color::Yellow);
			}
			else if (bonus.BonusType == 2)
			{
				if (player.lives < 6)
				{
					++player.lives;
				}
				player.score += 100;
				if (player.score > 999999999)
				{
					player.score = 999999999.0f;
				}
			}
			else if (bonus.BonusType == 3)
			{
				if (!player.isBig)
				{
					player.ball.setRadius(20);
					player.ball.setOrigin(player.ball.getGlobalBounds().width / 2, player.ball.getGlobalBounds().height / 2);
					player.playerSpeed = player.playerSpeed * 1.5f;
					player.isBig = true;
				}
			}
		}
		Collision collisions = GetCollisionsPlayer(player.ball, platforms, ceiling);

		if (collisions.platformIndex != -1)
		{
			if (platforms[collisions.platformIndex].isThorn)
			{
				if (!player.shield)
				{
					--player.lives;
				}
				player.status = Status::dead;
			}
			else
			{
				sf::Vector2f newPosition = { player.ball.getPosition().x, platforms[collisions.platformIndex].platform.getGlobalBounds().top };
				newPosition += {0, -player.ball.getGlobalBounds().height / 2};
				player.ball.setPosition(newPosition);
			}
		}

		if (collisions.collisionExtreme)
		{
			if (!player.shield)
			{
				--player.lives;
			}
			player.status = Status::dead;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (player.ball.getPosition().x > player.ball.getGlobalBounds().width / 2 && !collisions.collisionLeft)
			{
				float speed = -player.playerSpeed;
				if (player.isBig)
				{
					speed /= 1.5f;
				}
				player.ball.move(speed * time, 0);
			}
		};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (player.ball.getPosition().x < 400 - player.ball.getGlobalBounds().width / 2 && !collisions.collisionRight)
			{
				float speed = player.playerSpeed;
				if (player.isBig)
				{
					speed /= 1.5f;
				}
				player.ball.move(speed * time, 0);
			}
		};
		if (player.shield)
		{
			player.bonusTime -= time;
			if (player.bonusTime <= 0)
			{
				player.shield = false;
				player.bonusTime = 0;
				player.ball.setFillColor(sf::Color::Red);
			}
		}
		if (collisions.collisionDown)
		{
			player.ball.move(0, platformSpeed * time);
		}
		else
		{
			player.ball.move(0, player.playerSpeed * time);
			player.score += player.playerSpeed;
			player.playerSpeed = GetNewSpeed(player.score, player.isBig);
			platformSpeed = -player.playerSpeed;
			if (player.isBig)
			{
				platformSpeed /= 1.5;
			}
			if (player.score > 999999999)
			{
				player.score = 999999999.0f;
			}

		}
	}
}