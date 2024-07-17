#pragma once

#include <iostream>
#include <string>
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

class Piece
{
private:

protected:
    bool pieceColor;
    int row;
    int column;

    float xPosition;
    float yPosition;

    bool isClicked;

    sf::RectangleShape buttonShape;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Piece(bool pieceColor, int row, int column, sf::RenderTarget *target);
    virtual ~Piece();

    virtual void update(const sf::Vector2f mousePos) = 0;
    virtual void render(sf::RenderTarget *target) = 0;
};