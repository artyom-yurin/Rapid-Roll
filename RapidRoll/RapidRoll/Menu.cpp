#include "stdafx.h"
#include "Player.h"
#include "Menu.h"

sf::Sprite InitBackground(sf::Texture & texture)
{
	sf::Sprite backgroung;
	backgroung.setTexture(texture);
	backgroung.setTextureRect(sf::IntRect(15, 527, 400, 600));
	backgroung.setOrigin(backgroung.getGlobalBounds().width / 2, backgroung.getGlobalBounds().height / 2);
	backgroung.setPosition(200, 300);
	return backgroung;
}

sf::Sprite InitLogo(sf::Texture & texture)
{
	sf::Sprite logoSpace;
	logoSpace.setTexture(texture);
	logoSpace.setTextureRect(sf::IntRect(642, 4, 850, 410));
	logoSpace.setOrigin(logoSpace.getGlobalBounds().width / 2, logoSpace.getGlobalBounds().height / 2);
	logoSpace.scale(0.45f, 0.45f);
	logoSpace.setPosition(200, 200);
	return logoSpace;
}

sf::Sprite InitResult(sf::Texture & texture)
{
	sf::Sprite resultSpace;
	resultSpace.setTexture(texture);
	resultSpace.setTextureRect(sf::IntRect(447, 905, 578, 360));
	resultSpace.setOrigin(resultSpace.getGlobalBounds().width / 2, resultSpace.getGlobalBounds().height / 2);
	resultSpace.scale(0.5f, 0.5f);
	resultSpace.setPosition(200, 200);
	return resultSpace;
}

void InitFont(sf::Font & font)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error not find file with font" << std::endl;
		std::exit(1);
	}
}

void InitResultMessage(sf::Text & text, sf::Font const & font, int score)
{
	text.setFont(font);
	text.setCharacterSize(30);
	std::string message = std::to_string(score);
	text.setString(message);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(200, 200);
}

void InitMessage(sf::Text & text, sf::Font const & font, std::string const & message)
{
	text.setFont(font);
	text.setCharacterSize(30);
	text.setString(message);
	text.setFillColor(sf::Color::Blue);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(200, 400);
}

void InitMessageSpace(sf::RectangleShape & messageSpace)
{
	messageSpace.setSize({ 200, 150 });
	messageSpace.setFillColor(sf::Color::Yellow);
	messageSpace.setOrigin(messageSpace.getGlobalBounds().width / 2, messageSpace.getGlobalBounds().height / 2);
	messageSpace.setPosition(200, 400);
}

void InitLiveBalls(sf::CircleShape(&liveBalls)[5], int lives)
{
	for (int i = 0; i < 5; ++i)
	{
		liveBalls[i].setRadius(13);
		liveBalls[i].setOrigin(liveBalls[i].getGlobalBounds().width / 2, liveBalls[i].getGlobalBounds().height / 2);
		liveBalls[i].setPosition((float)i * 31 + 15, (float)15);
		if (i < lives)
		{
			liveBalls[i].setFillColor(sf::Color::Red);
		}
		else
		{
			liveBalls[i].setFillColor(sf::Color::Cyan);
		}
	}
}

void InitScore(sf::Text & text, sf::Font const & font)
{
	text.setFont(font);
	text.setCharacterSize(20);
	text.setString("Score: 000000000");
	text.setFillColor(sf::Color::White);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(300, 10);
}

void InitProgressBar(sf::RectangleShape & processBar, sf::CircleShape(&liveBalls)[5], int lives, sf::Text & scoreText, sf::Font const & font)
{
	processBar.setPosition(0, 0);
	sf::Vector2f barSize = { 400, 30 };
	processBar.setSize(barSize);
	processBar.setFillColor(sf::Color::Black);
	InitLiveBalls(liveBalls, lives);
	InitScore(scoreText, font);
}

void UpdateProgressBar(sf::CircleShape(&liveBalls)[5], const struct SPlayer & player, sf::Text & scoreText)
{
	for (int i = 0; i < 5; ++i)
	{
		if (i < player.lives)
		{
			liveBalls[i].setFillColor(sf::Color::Red);
		}
		else
		{
			liveBalls[i].setFillColor(sf::Color::Cyan);
		}
	}
	std::string result;
	std::string score = std::to_string((int)player.score);
	for (size_t i = 0; i < (9 - score.length()); ++i)
	{
		result += "0";
	}
	result += score;
	scoreText.setString("Score: " + result);
}

void LoadSprite(sf::Image & img, sf::Texture & texture)
{
	img.loadFromFile("images/sprite.png");
	texture.loadFromImage(img);
}
