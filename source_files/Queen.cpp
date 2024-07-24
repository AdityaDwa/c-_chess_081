#include "../header_files/Queen.h"

Queen::Queen(bool pieceColor, int row, int column, sf::Color btnColor, sf::RenderTarget *target) : Piece(pieceColor, row, column, btnColor, target)
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
        this->texture.loadFromFile("../src/white_queen.png");
    }
    else
    {
        this->texture.loadFromFile("../src/black_queen.png");
    }

    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    float scaleX = 120.f / this->sprite.getLocalBounds().width;
    float scaleY = 120.f / this->sprite.getLocalBounds().height;

    this->sprite.setScale(scaleX, scaleY);
    this->sprite.setPosition(this->xPosition, this->yPosition);
}

Queen::~Queen()
{
}

void Queen::update(const sf::Vector2f mousePos)
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

void Queen::render(sf::RenderTarget *target)
{
    target->draw(this->buttonShape);
    target->draw(this->sprite);
}

void Queen::possibleMoves(int row, int column, bool pieceColor, std::vector<std::vector<int>>& moveArray){
    int i = 1;
    while ((column + i) < 8)
    {
        moveArray.push_back({row, column + i});
        i++;
    }

    int j = 1;
    while ((column - j) >= 0)
    {
        moveArray.push_back({row, column - j});
        j++;
    }

    int k = 1;
    while ((row + k) < 8)
    {
        moveArray.push_back({row + k, column});
        k++;
    }

    int l = 1;
    while ((row - l) >= 0)
    {
        moveArray.push_back({row - l, column});
        l++;
    }

    int m = 1;
    while (((row + m) < 8) && ((column + m) < 8))
    {
        moveArray.push_back({row + m, column + m});
        m++;
    }
    
    int n = 1;
    while (((row + n) < 8) && ((column - n) >= 0))
    {
        moveArray.push_back({row + n, column - n});
        n++;
    }

    int o = 1;
    while (((row - o) >= 0) && ((column + o) < 8))
    {
        moveArray.push_back({row - o, column + o});
        o++;
    }

    int p = 1;
    while (((row - p) >= 0) && ((column - p) >= 0))
    {
        moveArray.push_back({row - p, column - p});
        p++;
    }
}