#include "../header_files/Piece.h"

Piece::Piece(bool pieceColor, int row, int column, sf::Color btnColor, sf::RenderTarget *target)
{
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