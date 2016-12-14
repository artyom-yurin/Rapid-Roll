#include "stdafx.h"
#include "Collision.h"
#include "Map.h"
#include "Player.h"

void InitFont(sf::Font & font)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error not find file with font" << std::endl;
			std::exit(1);
	}
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
	messageSpace.setSize({200, 150});
	messageSpace.setFillColor(sf::Color::Yellow);
	messageSpace.setOrigin(messageSpace.getGlobalBounds().width / 2, messageSpace.getGlobalBounds().height / 2);
	messageSpace.setPosition(200, 400);
}

struct Application
{
	sf::RenderWindow window;
	sf::CircleShape player;
	bool isPause;
	int countThorns;
	int lives;
	float platformSpeed;
	sf::RectangleShape platforms[10];
	sf::RectangleShape ceiling;
	sf::RectangleShape messageSpace;
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
		isPause = true;
		InitFont(font);
		InitMessage(message, font, "Press enter\nto start");
		InitMessageSpace(messageSpace);
		InitMap(platforms, countThorns, platformSpeed, ceiling);
		InitPlayer(player, platforms[0].getPosition());
	}

	void Update(sf::Int64 time)
	{
		UpdatePlayer(player, time, platformSpeed, lives, platforms);
		UpdateMap(platforms, time, platformSpeed, countThorns);
		if (!lives)
		{
			InitMessage(message, font, "Press enter\nto play again");
			InitMessageSpace(messageSpace);
		}
	}

	void Draw()
	{
		for (sf::RectangleShape platform : platforms)
		{
			window.draw(platform);
		}
		window.draw(ceiling);
		window.draw(player);
		if (!lives || isPause)
		{
			window.draw(messageSpace);
			window.draw(message);
			if (isPause)
			{
				//TODO: write game's name and massage "Press enter to start"
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
						InitMessageSpace(messageSpace);
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

