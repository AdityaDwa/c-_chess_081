#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <filesystem>

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

    sf::RectangleShape buttonShape;
    sf::Texture texture;
    sf::Sprite sprite;

    
    std::string pType;
    bool pColor;
    std::string pIdentifier;

public:
    Piece(bool pieceColor, int row, int column, sf::Color btnColor, sf::RenderTarget *target);
    virtual ~Piece();

    void movePiece(int currentRow, int currentColumn, int targetRow, int targetColumn);
    
    virtual void update(const sf::Vector2f mousePos) = 0;
    virtual void render(sf::RenderTarget *target) = 0;
    virtual void possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray) = 0;
};