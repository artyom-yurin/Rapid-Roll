#include "stdafx.h"
#include "Collision.h"
#include "Player.h"

void InitPlayer(sf::CircleShape & player, sf::Vector2f position)
{
	player.setRadius(15);
	player.setFillColor(sf::Color::Red);
	player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
	position += {0, -(player.getGlobalBounds().height / 2)};
	player.setPosition(position);
}

void UpdatePlayer(sf::CircleShape & player, sf::Int64 & time, float & platformSpeed, int & lives, sf::RectangleShape(&platforms)[10])
{
	Collision collisions = GetCollisions(player, platforms);

	if (collisions.platformIndex != -1)
	{
		if (platforms[collisions.platformIndex].getFillColor() == sf::Color::Red)
		{
			--lives;
			int startIndexPlatform = collisions.platformIndex;
			if (startIndexPlatform + 1 == 10)
			{
				startIndexPlatform -= 1;
			}
			else
			{
				startIndexPlatform += 1;
			}
			InitPlayer(player, platforms[startIndexPlatform].getPosition());
		}
	}

	if (collisions.collisionExtreme)
	{
		--lives;
		int startIndexPlatform = -1;
		int i = 0;
		while (startIndexPlatform == -1)
		{
			if (platforms[i].getGlobalBounds().top > 200 && platforms[i].getFillColor() != sf::Color::Red)
			{
				startIndexPlatform = i;
			}
			++i;
		}
		InitPlayer(player, platforms[startIndexPlatform].getPosition());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (player.getPosition().x > player.getGlobalBounds().width / 2 && !collisions.collisionLeft)
		{
			player.move(-0.1f * time, 0);
		}
	};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (player.getPosition().x < 400 - player.getGlobalBounds().width / 2 && !collisions.collisionRight)
		{
			player.move(0.1f * time, 0);
		}
	};
	if (collisions.collisionDown)
	{
		player.move(0, platformSpeed * time);
	}
	else
	{
		player.move(0, 0.1f * time);
	}
}