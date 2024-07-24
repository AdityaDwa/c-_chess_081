#include "../header_files/Knight.h"

Knight::Knight(bool pieceColor, int row, int column, sf::Color btnColor, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, target)
{
    this->row = row;
    this->column = column;
    this->xPosition = ((target->getSize().x - 960.f) / 2) + (row * 120.f);
    this->yPosition = ((target->getSize().y - 960.f) / 2) + ((7 - column) * 120.f);

    this->buttonShape.setPosition(sf::Vector2f(this->xPosition, this->yPosition));
    this->buttonShape.setSize(sf::Vector2f(120.f, 120.f));
    this->buttonShape.setFillColor(btnColor);

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
    static sf::Clock debounceClock;
    const sf::Time debounceTime = sf::milliseconds(200);

    if (this->buttonShape.getGlobalBounds().contains(mousePos))
    {
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (isPressed && debounceClock.getElapsedTime() > debounceTime)
        {
            std::ifstream sourceFile("../active_tiles.txt");
            std::ofstream destinationFile("../modifying_tiles.txt");
            std::string line;

            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    std::getline(sourceFile, line);
                    std::istringstream ss(line);

                    int num1, num2, num3;
                    char delimiter1, delimiter2;

                    if (ss >> num1 >> delimiter1 >> num2 >> delimiter2 >> num3)
                    {
                        if (num1 == this->row && num2 == this->column)
                        {
                            num3 = !num3;
                        }
                    }

                    destinationFile << num1 << ',' << num2 << ',' << num3 << std::endl;
                }
            }
            sourceFile.close();
            destinationFile.close();
            std::filesystem::remove("../active_tiles.txt");
            std::filesystem::rename("../modifying_tiles.txt", "../active_tiles.txt");

            debounceClock.restart();
        }
    }
}

void Knight::render(sf::RenderTarget *target)
{
    target->draw(this->buttonShape);
    target->draw(this->sprite);
}

void Knight::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray){
    bool up = (column + 2) < 8;
    bool down = (column - 2) >= 0;
    bool right = (row + 2) < 8;
    bool left = (row - 2) >= 0;

    if (((row + 1) < 8) && up)
    {
        moveArray.push_back({row + 1, column + 2});
    }

    if (((row - 1) >= 0) && up)
    {
        moveArray.push_back({row - 1, column + 2});
    }

    if (right && ((column + 1) < 8))
    {
        moveArray.push_back({row + 2, column + 1});
    }

    if (right && ((column - 1) >= 0))
    {
        moveArray.push_back({row + 2, column - 1});
    }
    
    if (((row + 1) < 8) && down)
    {
        moveArray.push_back({row + 1, column - 2});
    }

    if (((row - 1) >= 0) && down)
    {
        moveArray.push_back({row - 1, column - 2});
    }

    if (left && ((column + 1) < 8))
    {
        moveArray.push_back({row - 2, column + 1});
    }

    if (left && ((column - 1) >= 0))
    {
        moveArray.push_back({row - 2, column - 1});
    }
}