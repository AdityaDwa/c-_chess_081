#include "../header_files/Button.h"

Button::Button(int row, int column, int parentRow, int parentColumn, sf::RenderTarget *target)
{
    this->selfRow = row;
    this->selfColumn = column;
    this->parentRow = parentRow;
    this->parentColumn = parentColumn;

    this->xPosition = ((target->getSize().x - 960.f) / 2) + (row * 120.f);
    this->yPosition = ((target->getSize().y - 960.f) / 2) + ((7 - column) * 120.f);

    this->buttonShape.setPosition(sf::Vector2f(this->xPosition, this->yPosition));
    this->buttonShape.setSize(sf::Vector2f(120.f, 120.f));
    this->buttonShape.setFillColor(sf::Color(0, 0, 0, 0));

    this->texture.loadFromFile("../src/checkpawn.png");

    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    float scaleX = 120.f / this->sprite.getLocalBounds().width;
    float scaleY = 120.f / this->sprite.getLocalBounds().height;

    this->sprite.setScale(scaleX, scaleY);
    this->sprite.setPosition(this->xPosition, this->yPosition);
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f mousePos)
{
    static sf::Clock debounceClock;
    const sf::Time debounceTime = sf::milliseconds(200);

    if (this->buttonShape.getGlobalBounds().contains(mousePos))
    {
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (isPressed && debounceClock.getElapsedTime() > debounceTime)
        {
            std::ofstream filegone("../isClickedOn.txt");
            filegone << parentRow << ',' << parentColumn << ',' << selfRow << ',' << selfColumn << ',' << 1 << std::endl;
            filegone.close();
            debounceClock.restart();
        }
    }
}

void Button::render(sf::RenderTarget *target)
{
    target->draw(this->buttonShape);
    target->draw(this->sprite);
}