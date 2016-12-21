#pragma once

void InitLogoSpace(sf::RectangleShape & logoSpace);

void InitFont(sf::Font & font);

void InitMessage(sf::Text & text, sf::Font const & font, std::string const & message);

void InitMessageSpace(sf::RectangleShape & messageSpace);

void InitProgressBar(sf::RectangleShape & processBar, sf::CircleShape (&liveBalls)[5], int lives, int points);

void UpdateProgressBar(sf::CircleShape(&liveBalls)[5], int lives, int points);