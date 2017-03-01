#include "stdafx.h"
#include "Collision.h"
#include "Map.h"
#include "Player.h"
#include "Bonus.h"
#include "Menu.h"

struct Application
{
	sf::RenderWindow window;
	sf::Image image;
	sf::Texture texture;
	// игрок
	SPlayer player;
	// флаг паузы
	bool isPause;
	// счетчик до следующей платформы с шипами
	int countThorns;
	// скорость платформ
	float platformSpeed;
	// бонус
	SBonus bonus;
	// платформы
	SPlatform platforms[10];
	// место для меню
	sf::RectangleShape progressBar;
	// жизни героя
	sf::CircleShape liveBalls[5];
	// верхняя граница
	sf::Sprite ceiling;
	// окно сообщений
	sf::RectangleShape messageSpace;
	// лого игры
	sf::Sprite logoSpace;
	// результат игры
	sf::RectangleShape resultSpace;
	sf::Event event;
	sf::Font font;
	sf::Text message;
	sf::Text resultMessage;
	sf::Text scoreText;

	void InitWindow()
	{
		const int screenWidth = 400;
		const int screenHeight = 600;
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		window.create(sf::VideoMode(screenWidth, screenHeight), "Rapid Roll", sf::Style::Close, settings);
	}

	void InitApplication()
	{
		LoadSprite(image, texture);
		isPause = true;
		InitFont(font);
		InitMessage(message, font, "Press enter\nto start");
		InitMessageSpace(messageSpace);
		logoSpace = InitLogo(texture);
		InitSpace(resultSpace);
		bonus = InitBonus(texture);
		InitMap(platforms, countThorns, platformSpeed, bonus, texture);
		InitCeiling(ceiling, texture);
		player = InitPlayer(platforms[0].platform.getPosition());
		InitProgressBar(progressBar, liveBalls, player.lives, scoreText, font);
	}

	void Update(sf::Int64 time)
	{
		UpdatePlayer(player, time, platformSpeed, platforms, bonus, ceiling);
		UpdateProgressBar(liveBalls, player, scoreText);
		if (bonus.needDraw)
		{
			UpdateBonus(bonus, time, platformSpeed, platforms);
		}
		UpdateMap(platforms, time, platformSpeed, countThorns, bonus, texture);
		if (!player.lives)
		{
			InitResultMessage(resultMessage, font, (int)player.score);
			InitMessage(message, font, "Press enter\nto play again");
		}
	}

	void Draw()
	{
		for (SPlatform platform : platforms)
		{
			window.draw(platform.platform);
		}
		if (bonus.needDraw)
		{
			window.draw(bonus.bonus);
		}
		window.draw(ceiling);
		window.draw(progressBar);
		for (sf::CircleShape liveBall : liveBalls)
		{
			window.draw(liveBall);
		}
		window.draw(scoreText);
		if (player.status == Status::live)
		{
			window.draw(player.ball);
		}
		if (!player.lives || isPause)
		{
			window.draw(messageSpace);
			window.draw(message);
			if (isPause)
			{
				window.draw(logoSpace);
			}
			else if (!player.lives)
			{
				window.draw(resultSpace);
				window.draw(resultMessage);
			}
		}
	}

	void HandleEvents()
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					isPause = !isPause;
					if (isPause)
					{
						if (!player.lives)
						{
							InitApplication();
						}
						InitMessage(message, font, "Press enter\nto start");
					}
				}
			}
		}
	}
};

int main()
{
	Application app;
	app.InitWindow();

	app.InitApplication();
	
	sf::Clock clock;
	while (app.window.isOpen())
	{
		sf::Int64 time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600;

		app.HandleEvents();

		if (app.player.lives && !app.isPause)
		{
			app.Update(time);
		}

		app.window.clear(sf::Color::White);

		app.Draw();

		app.window.display();
	}

    return 0;
}

