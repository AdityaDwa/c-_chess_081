#include "../header_files/Piece.h"

Piece::Piece(bool pieceColor, int row, int column, sf::Color btnColor, sf::RenderTarget *target)
{
}

Piece::~Piece()
{
}

void Piece::move(int currentRow, int currentColumn, int targetRow, int targetColumn)
{
    // std::ifstream sourceFile("../piece_info.txt");
    // std::ofstream destinationFile("../move_pieces.txt");
    // std::string line;
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         std::getline(sourceFile, line);
    //         std::istringstream ss(line);

    //         int row, col;
    //         std::string pieceType;
    //         bool pieceColor;
    //         std::string pieceIdentifier;

    //         ss >> row;
    //         ss.ignore(1, ',');

    //         ss >> col;
    //         ss.ignore(1, ',');

    //         std::getline(ss, pieceType, ',');
    //         // if (ss.fail())
    //             // continue;

    //         ss >> std::boolalpha >> pieceColor;
    //         // if (ss.fail() || ss.peek() != ',')
    //             // continue;
    //         ss.ignore(1, ',');

    //         std::getline(ss, pieceIdentifier);
    //         // if (ss.fail())
    //             // continue;

    //         pieceType = pieceType.substr(pieceType.find_first_not_of(" \t"));
    //         pieceIdentifier = pieceIdentifier.substr(pieceIdentifier.find_first_not_of(" \t"));

    //         if (row == currentRow && col == currentColumn)
    //         {
    //             destinationFile << row << ',' << column << ',' << ',' << ',' << std::endl;
    //             this->pType = pieceType;
    //             this->pColor = pieceColor;
    //             this->pIdentifier = pieceIdentifier;
    //         }
    //         else{
    //             destinationFile << row << ',' << column << ',' << pieceType << ',' << pieceColor << ',' << pieceIdentifier << std::endl;
    //         }
            
    //     }
    // }
    // sourceFile.close();
    // destinationFile.close();
    // std::filesystem::remove("../piece_info.txt");
    // std::filesystem::rename("../move_pieces.txt", "../piece_info.txt");

    // std::ifstream csourceFile("../piece_info.txt");
    // std::ofstream cdestinationFile("../move_pieces.txt");
    // std::string cline;
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         std::getline(csourceFile, cline);
    //         std::istringstream ss(cline);

    //         int row, col;
    //         std::string pieceType;
    //         bool pieceColor;
    //         std::string pieceIdentifier;

    //         ss >> row;
    //         ss.ignore(1, ',');

    //         ss >> col;
    //         ss.ignore(1, ',');

    //         std::getline(ss, pieceType, ',');
    //         // if (ss.fail())
    //             // continue;

    //         ss >> std::boolalpha >> pieceColor;
    //         // if (ss.fail() || ss.peek() != ',')
    //             // continue;
    //         ss.ignore(1, ',');

    //         std::getline(ss, pieceIdentifier);
    //         // if (ss.fail())
    //             // continue;

    //         pieceType = pieceType.substr(pieceType.find_first_not_of(" \t"));
    //         pieceIdentifier = pieceIdentifier.substr(pieceIdentifier.find_first_not_of(" \t"));

    //         if (row == targetRow && col == targetColumn)
    //         {
    //             cdestinationFile << row << ',' << column << ',' << this->pType << ',' << this->pColor << ',' << this->pIdentifier << std::endl;
    //         }
    //         else{
    //             cdestinationFile << row << ',' << column << ',' << pieceType << ',' << pieceColor << ',' << pieceIdentifier << std::endl;
    //         }
            
    //     }
    // }
    // csourceFile.close();
    // cdestinationFile.close();
    // std::filesystem::remove("../piece_info.txt");
    // std::filesystem::rename("../move_pieces.txt", "../piece_info.txt");
}