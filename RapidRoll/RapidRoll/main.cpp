#include "stdafx.h"
#include "Collision.h"
#include "Map.h"
#include "Player.h"
#include "Menu.h"

struct Application
{
	sf::RenderWindow window;
	sf::CircleShape player;
	bool isPause;
	int countThorns;
	int lives;
	int points;
	float platformSpeed;
	sf::RectangleShape platforms[10];
	sf::RectangleShape progressBar;
	sf::CircleShape liveBalls[5];
	sf::RectangleShape ceiling;
	sf::RectangleShape messageSpace;
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
		lives = 3;
		points = 0;
		isPause = true;
		InitFont(font);
		InitMessage(message, font, "Press enter\nto start");
		InitMessageSpace(messageSpace);
		InitLogoSpace(logoSpace);
		InitMap(platforms, countThorns, platformSpeed);
		InitCeiling(ceiling);
		InitPlayer(player, platforms[0].getPosition());
		InitProgressBar(progressBar, liveBalls, lives, points);
	}

	void Update(sf::Int64 time)
	{
		UpdatePlayer(player, time, platformSpeed, lives, platforms);
		UpdateProgressBar(liveBalls, lives, points);
		UpdateMap(platforms, time, platformSpeed, countThorns);
		if (!lives)
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
		window.draw(ceiling);
		window.draw(progressBar);
		for (sf::CircleShape liveBall : liveBalls)
		{
			window.draw(liveBall);
		}
		window.draw(player);
		if (!lives || isPause)
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
						if (!lives)
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

		if (app.lives && !app.isPause)
		{
			app.Update(time);
		}

		app.window.clear(sf::Color::White);

		app.Draw();

		app.window.display();
	}

    return 0;
}

