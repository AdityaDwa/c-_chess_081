#include "../header_files/Knight.h"

Knight::Knight(bool pieceColor, int row, int column, sf::RenderTarget *target) : Piece(pieceColor, row, column, target)
{
    this->xPosition = ((target->getSize().x - 960.f) / 2) + (row * 120.f);
    this->yPosition = ((target->getSize().y - 960.f) / 2) + ((7 - column) * 120.f);

    this->buttonShape.setPosition(sf::Vector2f(this->xPosition, this->yPosition));
    this->buttonShape.setSize(sf::Vector2f(120.f, 120.f));
    this->buttonShape.setFillColor(sf::Color(0, 0, 0, 0));

    if (pieceColor)
    {
        this->texture.loadFromFile("../src/white_knight.png");
    }
    else
    {
        this->texture.loadFromFile("../src/black_knight.png");
    }

    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    float scaleX = 120.f / this->sprite.getLocalBounds().width;
    float scaleY = 120.f / this->sprite.getLocalBounds().height;

    this->sprite.setScale(scaleX, scaleY);
    this->sprite.setPosition(this->xPosition, this->yPosition);
}

Knight::~Knight()
{
}

void Knight::update(const sf::Vector2f mousePos)
{
}

void Knight::render(sf::RenderTarget *target)
{
    target->draw(this->buttonShape);
    target->draw(this->sprite);
}