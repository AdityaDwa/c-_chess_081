#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Button
{
private:

    sf::RectangleShape buttonShape;
    sf::Font *font;
    sf::Text innerText;

    sf::Texture texture;
    sf::Sprite sprite;
    bool hasImage;

    sf::Color defaultColor;
    sf::Color focusedColor;
    
public:
    Button(float x, float y, float width, float height, sf::Font *font, std::string innerText, sf::Color defaultColor, sf::Color focusedColor, std::string imagePath = "");
    ~Button();

    bool isClicked;

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget *target);
};
