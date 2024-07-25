#include "../header_files/Button.h"

Button::Button(int row, int column, int parentRow, int parentColumn, bool parentColor, sf::RenderTarget *target)
{
    bool targetColor = parentColor;
    std::ifstream sourceFile("../pieces_info.txt");
    std::string line;

    while (std::getline(sourceFile, line))
    {
        std::istringstream ss(line);

        int r, c;
        std::string pieceType;
        bool pieceColor;
        std::string pieceIdentifier;

        ss >> r;
        ss.ignore(1, ',');

        ss >> c;
        ss.ignore(1, ',');

        std::getline(ss, pieceType, ',');
        if (ss.fail())
            continue;

        ss >> pieceColor;
        if (ss.fail())
            continue;
        ss.ignore(1, ',');

        std::getline(ss, pieceIdentifier);
        if (ss.fail())
            continue;

        if (r == row && c == column)
        {
            targetColor = pieceColor;
        }
    }
    sourceFile.close();

    this->selfRow = row;
    this->selfColumn = column;
    this->parentRow = parentRow;
    this->parentColumn = parentColumn;

    this->xPosition = ((target->getSize().x - 960.f) / 2) + (row * 120.f);
    this->yPosition = ((target->getSize().y - 960.f) / 2) + ((7 - column) * 120.f);

    this->buttonShape.setPosition(sf::Vector2f(this->xPosition, this->yPosition));
    this->buttonShape.setSize(sf::Vector2f(120.f, 120.f));
    this->buttonShape.setFillColor(sf::Color(0, 0, 0, 0));

    if (targetColor != parentColor)
    {
        this->texture.loadFromFile("../src/capture_tile.png");
    }
    else
    {
        this->texture.loadFromFile("../src/movable_tile.png");
    }

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