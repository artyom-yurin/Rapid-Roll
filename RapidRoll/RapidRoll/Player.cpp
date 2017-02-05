#include "stdafx.h"
#include "Bonus.h"
#include "Collision.h"
#include "Player.h"

void ResetPlayer(SPlayer & player, sf::Vector2f position)
{
	player.ball.setRadius(15);
	player.ball.setOrigin(player.ball.getGlobalBounds().width / 2, player.ball.getGlobalBounds().height / 2);
	player.ball.setFillColor(sf::Color::Red);
	player.status = Status::live;
	position += {0, -(player.ball.getGlobalBounds().height / 2)};
	player.ball.setPosition(position);
	player.playerSpeed = 0.1f;
	player.shield = false;
	player.bonusTime = 0;
}

SPlayer InitPlayer(sf::Vector2f position)
{
	SPlayer player;
	player.status = Status::live;
	player.lives = 3;
	player.playerSpeed = 0.1f;
	player.ball.setRadius(15);
	player.ball.setFillColor(sf::Color::Red);
	player.ball.setOrigin(player.ball.getGlobalBounds().width / 2, player.ball.getGlobalBounds().height / 2);
	position += {0, -(player.ball.getGlobalBounds().height / 2)};
	player.ball.setPosition(position);
	return player;
}

void UpdatePlayer(SPlayer & player, sf::Int64 & time, float platformSpeed, sf::RectangleShape(&platforms)[10], SBonus & bonus)
{
	if (player.status == Status::dead)
	{
		player.indexRespawn = -1;
		int i = 0;
		for (sf::RectangleShape platform: platforms)
		{
			if (platform.getGlobalBounds().top > 300 && platform.getGlobalBounds().top < 400 && platform.getFillColor() != sf::Color::Red)
			{
				player.indexRespawn = i;
			}
			++i;
		}
		if (player.indexRespawn != -1)
		{
			ResetPlayer(player, platforms[player.indexRespawn].getPosition());
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
				player.ball.setRadius(20);
				player.ball.setOrigin(player.ball.getGlobalBounds().width / 2, player.ball.getGlobalBounds().height / 2);
				player.playerSpeed = 0.15f;
			}
			else
			{
				if (player.lives < 6)
				{
					++player.lives;
				}
			}
		}
		Collision collisions = GetCollisionsPlayer(player.ball, platforms);

		if (collisions.platformIndex != -1)
		{
			if (platforms[collisions.platformIndex].getFillColor() == sf::Color::Red)
			{
				if (!player.shield)
				{
					--player.lives;
				}
				player.status = Status::dead;
			}
			else
			{
				sf::Vector2f newPosition = { player.ball.getPosition().x, platforms[collisions.platformIndex].getGlobalBounds().top };
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
				player.ball.move(-0.1f * time, 0);
			}
		};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (player.ball.getPosition().x < 400 - player.ball.getGlobalBounds().width / 2 && !collisions.collisionRight)
			{
				player.ball.move(0.1f * time, 0);
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
		}
	}
}