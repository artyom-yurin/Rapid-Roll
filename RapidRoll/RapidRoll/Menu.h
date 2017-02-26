#pragma once

void InitSpace(sf::RectangleShape & logoSpace);

void InitFont(sf::Font & font);

void InitResultMessage(sf::Text & text, sf::Font const & font, int score);

void InitMessage(sf::Text & text, sf::Font const & font, std::string const & message);

void InitMessageSpace(sf::RectangleShape & messageSpace);

void InitProgressBar(sf::RectangleShape & processBar, sf::CircleShape(&liveBalls)[5], int lives, sf::Text & scoreText, sf::Font const & font);

void UpdateProgressBar(sf::CircleShape(&liveBalls)[5], const struct SPlayer & player, sf::Text & scoreText);

void LoadSprite(sf::Image & img, sf::Texture & texture);
