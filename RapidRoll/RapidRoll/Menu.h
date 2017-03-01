#pragma once

sf::Sprite InitBackground(sf::Texture & texture);

sf::Sprite InitLogo(sf::Texture & texture);

sf::Sprite InitResult(sf::Texture & texture);

void InitFont(sf::Font & font);

void InitResultMessage(sf::Text & text, sf::Font const & font, int score);

sf::Sprite InitMessageSpace(sf::Texture & texture);

void InitProgressBar(sf::RectangleShape & processBar, sf::CircleShape(&liveBalls)[5], int lives, sf::Text & scoreText, sf::Font const & font);

void UpdateProgressBar(sf::CircleShape(&liveBalls)[5], const struct SPlayer & player, sf::Text & scoreText);

void LoadSprite(sf::Image & img, sf::Texture & texture);
