#include "../header_files/Piece.h"

Piece::Piece(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target)
{
    this->row = row;
    this->column = column;
    this->pieceColor = pieceColor;
    this->xPosition = ((target->getSize().x - 960.f) / 2) + (row * 120.f);
    this->yPosition = ((target->getSize().y - 960.f) / 2) + ((7 - column) * 120.f);

    this->buttonShape.setPosition(sf::Vector2f(this->xPosition, this->yPosition));
    this->buttonShape.setSize(sf::Vector2f(120.f, 120.f));
    this->buttonShape.setFillColor(btnColor);

    this->texture.loadFromFile(imagePath);
    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    float scaleX = 120.f / this->sprite.getLocalBounds().width;
    float scaleY = 120.f / this->sprite.getLocalBounds().height;

    this->sprite.setScale(scaleX, scaleY);
    this->sprite.setPosition(this->xPosition, this->yPosition);
}

Piece::~Piece()
{
}

void Piece::movePiece(int currentRow, int currentColumn, int targetRow, int targetColumn)
{
    std::ifstream sourceFile("../pieces_info.txt");
    std::string line;

    while (std::getline(sourceFile, line))
    {
        std::istringstream ss(line);

        int row, col;
        std::string pieceType;
        bool pieceColor;
        std::string pieceIdentifier;

        ss >> row;
        ss.ignore(1, ',');

        ss >> col;
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

        pieceType = pieceType.substr(pieceType.find_first_not_of(" \t"));
        pieceIdentifier = pieceIdentifier.substr(pieceIdentifier.find_first_not_of(" \t"));

        if (row == currentRow && col == currentColumn)
        {
            this->pType = pieceType;
            this->pColor = pieceColor;
            this->pIdentifier = pieceIdentifier;
            break;
        }
    }
    sourceFile.close();

    std::ifstream csourceFile("../pieces_info.txt");
    std::ofstream cdestinationFile("../move_pieces.txt");
    std::string cline;

    while (std::getline(csourceFile, cline))
    {
        std::istringstream sscord(cline);

        int row, col;

        sscord >> row;
        sscord.ignore(1, ',');

        sscord >> col;
        sscord.ignore(1, ',');

        if (row == targetRow && col == targetColumn)
        {
            cdestinationFile << row << ',' << col << ',' << this->pType << ',' << this->pColor << ',' << this->pIdentifier << std::endl;
        }
        else if (row == currentRow && col == currentColumn)
        {
            cdestinationFile << row << ',' << col << ',' << ',' << ',' << std::endl;
        }
        else
        {
            cdestinationFile << cline << std::endl;
        }
    }
    csourceFile.close();
    cdestinationFile.close();
    std::filesystem::remove("../pieces_info.txt");
    std::filesystem::rename("../move_pieces.txt", "../pieces_info.txt");

    std::ifstream dsourceFile("../active_tiles.txt");
    std::ofstream ddestinationFile("../reset.txt");
    std::string dline;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::getline(dsourceFile, dline);
            std::istringstream ssd(dline);

            int num1, num2, num3;
            char delimiter1, delimiter2;

            ssd >> num1 >> delimiter1 >> num2 >> delimiter2 >> num3;

            ddestinationFile << num1 << ',' << num2 << ',' << 0 << std::endl;
        }
    }

    dsourceFile.close();
    ddestinationFile.close();
    std::filesystem::remove("../active_tiles.txt");
    std::filesystem::rename("../reset.txt", "../active_tiles.txt");
}

std::vector<std::vector<std::string>> Piece::readBoardState()
{
    std::vector<std::vector<std::string>> boardState(8, std::vector<std::string>(8, ""));
    std::ifstream file("../pieces_info.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        int row, column, color;
        std::string piece, identifier;

        ss >> row;
        ss.ignore(1, ',');

        ss >> column;
        ss.ignore(1, ',');

        std::getline(ss, piece, ',');
        if (ss.fail())
            continue;

        ss >> color;
        if (ss.fail())
            continue;
        ss.ignore(1, ',');

        std::getline(ss, identifier);
        if (ss.fail())
            continue;

        boardState[row][column] = piece + "," + std::to_string(color);
    }

    return boardState;
}

void Piece::update(const sf::Vector2f mousePos)
{
    std::ifstream filler("../turn.txt");
    bool turnNum;
    filler >> turnNum;
    filler.close();

    // std::ofstream test("../logs/templog.txt");
    // std::string player = turnNum ? "White" : "Black";
    // test << player << " turn";
    // test.close();
    
    if (turnNum == this->pieceColor)
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
                            else
                            {
                                num3 = 0;
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
}

void Piece::render(sf::RenderTarget *target)
{
    target->draw(this->buttonShape);
    target->draw(this->sprite);
}
