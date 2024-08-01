#include "../header_files/Button.h"

Button::Button(int row, int column, int parentRow, int parentColumn, bool parentColor, sf::RenderTarget *target)
{
    bool targetColor = parentColor;
    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
    std::string infoLine;

    while (std::getline(currentPositionFile, infoLine))
    {
        std::istringstream infoString(infoLine);

        int r, c;
        std::string pieceType;
        bool pieceColor;
        std::string pieceIdentifier;

        infoString >> r;
        infoString.ignore(1, ',');

        infoString >> c;
        infoString.ignore(1, ',');

        std::getline(infoString, pieceType, ',');
        if (infoString.fail())
            continue;

        infoString >> pieceColor;
        if (infoString.fail())
            continue;
        infoString.ignore(1, ',');

        std::getline(infoString, pieceIdentifier);
        if (infoString.fail())
            continue;

        if (r == row && c == column)
        {
            targetColor = pieceColor;
        }
    }
    currentPositionFile.close();

    this->selfRow = row;
    this->selfColumn = column;
    this->parentRow = parentRow;
    this->parentColumn = parentColumn;

    bool playerTurn;
    std::ifstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile >> playerTurn;
    playerTurnFile.close();

    if (playerTurn)
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

    std::ifstream mousePositionFile("../templates/mouse_position.txt");
    mousePositionFile >> clicked >> del1 >> mouseX >> del2 >> mouseY;
    mousePositionFile.close();

    sf::Vector2f clickPosition(mouseX, mouseY);

    if (clicked)
    {
        if (this->sprite.getGlobalBounds().contains(clickPosition))
        {
            std::ofstream isButtonClickedFile("../templates/is_button_clicked.txt");
            isButtonClickedFile << parentRow << ',' << parentColumn << ',' << selfRow << ',' << selfColumn << ',' << 1 << std::endl;
            isButtonClickedFile.close();

            std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
            mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
            mousePositionFile_1.close();
        }
    }
}

void Button::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}