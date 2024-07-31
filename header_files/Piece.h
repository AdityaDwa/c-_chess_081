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

    sf::Texture texture;
    sf::Sprite sprite;

    
    std::string movingPieceType;
    bool movingPieceColor;
    std::string movingPieceIdentifier;

public:
    Piece(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target);
    virtual ~Piece();

    void movePiece(int currentRow, int currentColumn, int targetRow, int targetColumn);
    std::vector<std::vector<std::string>> readBoardState();

    void update();
    void render(sf::RenderTarget *target);

    virtual void possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray) = 0;
    virtual void filterValidMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray, const std::vector<std::vector<std::string>>& boardState) = 0;
};