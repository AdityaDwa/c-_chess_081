#include "../header_files/Piece.h"

Piece::Piece(bool pieceColor, int row, int column, sf::Color btnColor, std::string imagePath, sf::RenderTarget *target)
{
    this->pieceColor = pieceColor;
    this->row = row;
    this->column = column;

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
    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
    std::string infoLine;

    while (std::getline(currentPositionFile, infoLine))
    {
        std::istringstream infoString(infoLine);

        int row, col;
        std::string pieceType;
        bool pieceColor;
        std::string pieceIdentifier;

        infoString >> row;
        infoString.ignore(1, ',');

        infoString >> col;
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

        pieceType = pieceType.substr(pieceType.find_first_not_of(" \t"));
        pieceIdentifier = pieceIdentifier.substr(pieceIdentifier.find_first_not_of(" \t"));

        if (row == currentRow && col == currentColumn)
        {
            this->movingPieceType = pieceType;
            this->movingPieceColor = pieceColor;
            this->movingPieceIdentifier = pieceIdentifier;
            break;
        }
    }
    currentPositionFile.close();

    std::ifstream currentPositionFile_1("../templates/current_piece_position.txt");
    std::ofstream tempMoveFile("../templates/moving_piece.txt");
    std::string infoLine_1;

    while (std::getline(currentPositionFile_1, infoLine_1))
    {
        std::istringstream infoString(infoLine_1);

        int row, col;

        infoString >> row;
        infoString.ignore(1, ',');

        infoString >> col;
        infoString.ignore(1, ',');

        if (row == targetRow && col == targetColumn)
        {
            tempMoveFile << row << ',' << col << ',' << this->movingPieceType << ',' << this->movingPieceColor << ',' << this->movingPieceIdentifier << std::endl;
        }
        else if (row == currentRow && col == currentColumn)
        {
            tempMoveFile << row << ',' << col << ',' << ',' << ',' << std::endl;
        }
        else
        {
            tempMoveFile << infoLine_1 << std::endl;
        }
    }
    currentPositionFile_1.close();
    tempMoveFile.close();
    std::filesystem::remove("../templates/current_piece_position.txt");
    std::filesystem::rename("../templates/moving_piece.txt", "../templates/current_piece_position.txt");

    std::ifstream tileInactivatorFile("../templates/inactive_all_tiles.txt");
    std::ofstream activeTileInfoFile("../templates/active_tile_info.txt");
    std::string inactivateLine;

    while (std::getline(tileInactivatorFile, inactivateLine))
    {
        activeTileInfoFile << inactivateLine << std::endl;
    }
    tileInactivatorFile.close();
    activeTileInfoFile.close();
}

std::vector<std::vector<std::string>> Piece::readBoardState()
{
    std::vector<std::vector<std::string>> boardState(8, std::vector<std::string>(8, ""));
    std::ifstream currentPositionFile("../templates/current_piece_position.txt");
    std::string infoLine;

    while (std::getline(currentPositionFile, infoLine))
    {
        std::stringstream infoString(infoLine);
        int row, column, color;
        std::string piece, identifier;

        infoString >> row;
        infoString.ignore(1, ',');

        infoString >> column;
        infoString.ignore(1, ',');

        std::getline(infoString, piece, ',');
        if (infoString.fail())
            continue;

        infoString >> color;
        if (infoString.fail())
            continue;
        infoString.ignore(1, ',');

        std::getline(infoString, identifier);
        if (infoString.fail())
            continue;

        boardState[row][column] = piece + "," + std::to_string(color);
    }

    return boardState;
}

void Piece::update()
{
    bool playerTurn;
    std::ifstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile >> playerTurn;
    playerTurnFile.close();

    if (playerTurn == this->pieceColor)
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
                std::ifstream activeTileInfoFile("../templates/active_tile_info.txt");
                std::ofstream changeActiveTileFile("../templates/change_active_tile.txt");
                std::string activeInfoLine;

                for (int i = 0; i < 8; ++i)
                {
                    for (int j = 0; j < 8; ++j)
                    {
                        std::getline(activeTileInfoFile, activeInfoLine);
                        std::istringstream activeInfoString(activeInfoLine);

                        int num1, num2, num3;
                        char delimiter1, delimiter2;

                        if (activeInfoString >> num1 >> delimiter1 >> num2 >> delimiter2 >> num3)
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

                        changeActiveTileFile << num1 << ',' << num2 << ',' << num3 << std::endl;
                    }
                }
                activeTileInfoFile.close();
                changeActiveTileFile.close();
                std::filesystem::remove("../templates/active_tile_info.txt");
                std::filesystem::rename("../templates/change_active_tile.txt", "../templates/active_tile_info.txt");

                std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
                mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
                mousePositionFile_1.close();
            }
        }
    }
}

void Piece::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}
