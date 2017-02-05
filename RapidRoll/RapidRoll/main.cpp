#include "stdafx.h"
#include "Collision.h"
#include "Map.h"
#include "Player.h"
#include "Bonus.h"
#include "Menu.h"

struct Application
{
	sf::RenderWindow window;
	// игрок
	SPlayer player;
	// флаг паузы
	bool isPause;
	// счетчик до следующей платформы с шипами
	int countThorns;
	// очки
	int points;
	// скорость платформ
	float platformSpeed;
	// бонус
	SBonus bonus;
	// платформы
	sf::RectangleShape platforms[10];
	// место для меню
	sf::RectangleShape progressBar;
	// жизни героя
	sf::CircleShape liveBalls[5];
	// верхняя граница
	sf::RectangleShape ceiling;
	// окно сообщений
	sf::RectangleShape messageSpace;
	// лого игры
	sf::RectangleShape logoSpace;
	sf::Event event;
	sf::Font font;
	sf::Text message;

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
		points = 0;
		isPause = true;
		InitFont(font);
		InitMessage(message, font, "Press enter\nto start");
		InitMessageSpace(messageSpace);
		InitLogoSpace(logoSpace);
		bonus = InitBonus();
		InitMap(platforms, countThorns, platformSpeed, bonus);
		InitCeiling(ceiling);
		player = InitPlayer(platforms[0].getPosition());
		InitProgressBar(progressBar, liveBalls, player.lives, points);
	}

	void Update(sf::Int64 time)
	{
		UpdatePlayer(player, time, platformSpeed, platforms, bonus);
		UpdateProgressBar(liveBalls, player.lives, points);
		if (bonus.needDraw)
		{
			UpdateBonus(bonus, time, platformSpeed, platforms);
		}
		UpdateMap(platforms, time, platformSpeed, countThorns, bonus);
		if (!player.lives)
		{
			InitMessage(message, font, "Press enter\nto play again");
		}
	}

	void Draw()
	{
		for (sf::RectangleShape platform : platforms)
		{
			window.draw(platform);
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

