#include "../header_files/Pawn.h"

Pawn::Pawn(bool pieceColor, int row, int column, float boardSquareSize, float boardDimension, sf::RenderTarget *target) : Piece(pieceColor, row, column, boardSquareSize, boardDimension, target)
{
    this->xPosition = ((target->getSize().x - boardDimension) / 2) + (row * boardSquareSize);
    this->yPosition = ((target->getSize().y - boardDimension) / 2) + ((7 - column) * boardSquareSize);

    this->buttonShape.setPosition(sf::Vector2f(this->xPosition, this->yPosition));
    this->buttonShape.setSize(sf::Vector2f(boardSquareSize, boardSquareSize));
    this->buttonShape.setFillColor(sf::Color(0, 0, 0, 0));

    if (pieceColor)
    {
        this->texture.loadFromFile("../src/white_pawn.png"); // handle error
    }
    else
    {
        this->texture.loadFromFile("../src/black_pawn.png");
    }

    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    float scaleX = boardSquareSize / this->sprite.getLocalBounds().width;
    float scaleY = boardSquareSize / this->sprite.getLocalBounds().height;

    this->sprite.setScale(scaleX, scaleY);
    this->sprite.setPosition(this->xPosition, this->yPosition);
}

Pawn::~Pawn()
{
}

void Pawn::update(const sf::Vector2f mousePos)
{
    // this->buttonShape.setFillColor(sf::Color(0, 0, 0, 0));

    // this->isClicked = false;
    // if (this->buttonShape.getGlobalBounds().contains(mousePos)) {
    //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //         this->buttonShape.setFillColor(sf::Color(169, 169, 169));
    //         this->isClicked = true;
    //     }
    //     else {
    //         this->isClicked = false;
    //     }

    // }
}

void Pawn::render(sf::RenderTarget *target)
{
    target->draw(this->buttonShape);
    target->draw(this->sprite);
}