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

    bool whoseTurn;
    std::ifstream turner("../turn.txt");
    turner >> whoseTurn;
    turner.close();

    if (whoseTurn)
    {
        this->xPosition = ((target->getSize().x - 960.f) / 2) + (row * 120.f);
        this->yPosition = ((target->getSize().y - 960.f) / 2) + ((7 - column) * 120.f);
    }
    else
    {
        this->xPosition = ((target->getSize().x - 960.f) / 2) + (std::abs(row - 7) * 120.f);
        this->yPosition = ((target->getSize().y - 960.f) / 2) + ((7 - std::abs(column - 7)) * 120.f);
    }

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

void Button::update()
{
    bool clicked;
    char del1, del2;
    float mouseX, mouseY;

    std::ifstream test("../mouse_position.txt");
    test >> clicked >> del1 >> mouseX >> del2 >> mouseY;
    test.close();

    sf::Vector2f clickPosition(mouseX, mouseY);

    if (clicked)
    {
        if (this->sprite.getGlobalBounds().contains(clickPosition))
        {
            std::ofstream filegone("../isClickedOn.txt");
            filegone << parentRow << ',' << parentColumn << ',' << selfRow << ',' << selfColumn << ',' << 1 << std::endl;
            filegone.close();

            std::ofstream idk("../mouse_position.txt");
            idk << 0 << ',' << 0 << ',' << 0;
            idk.close();
        }
    }
}

void Button::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}