#include "../header_files/Game.h"

void Game::initWindow()
{
    // this->window = new sf::RenderWindow(sf::VideoMode(1728, 972), "Chess", sf::Style::Default);
    this->window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "Chess", sf::Style::Fullscreen);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(true);
}

void Game::initApplication()
{
    std::ifstream initialPositionFile("../templates/initial_piece_position.txt");
    std::ofstream currentPositionFile("../templates/current_piece_position.txt");
    std::ofstream tempPositionFile("../templates/temp_piece_position.txt");
    std::string infoLine;

    while (std::getline(initialPositionFile, infoLine))
    {
        currentPositionFile << infoLine << std::endl;
        tempPositionFile << infoLine << std::endl;
    }

    initialPositionFile.close();
    currentPositionFile.close();
    tempPositionFile.close();

    std::ifstream tileInactivatorFile("../templates/inactive_all_tiles.txt");
    std::ofstream activeTileInfoFile("../templates/active_tile_info.txt");
    std::string inactivateLine;

    while (std::getline(tileInactivatorFile, inactivateLine))
    {
        activeTileInfoFile << inactivateLine << std::endl;
    }
    tileInactivatorFile.close();
    activeTileInfoFile.close();

    std::ofstream isButtonClickedFile("../templates/is_button_clicked.txt");
    isButtonClickedFile.close();

    std::ofstream playerTurnFile("../templates/player_turn.txt");
    playerTurnFile << 1;
    playerTurnFile.close();

    std::ofstream mousePositionFile("../templates/mouse_position.txt");
    mousePositionFile << 0 << ',' << 0 << ',' << 0;
    mousePositionFile.close();

    std::ofstream whiteKingCastleFile("../templates/white_king_castle.txt");
    whiteKingCastleFile << 0;
    whiteKingCastleFile.close();

    std::ofstream whiteRightRookCastleFile("../templates/white_right_rook_castle.txt");
    whiteRightRookCastleFile << 0;
    whiteRightRookCastleFile.close();

    std::ofstream whiteLeftRookCastleFile("../templates/white_left_rook_castle.txt");
    whiteLeftRookCastleFile << 0;
    whiteLeftRookCastleFile.close();

    std::ofstream blackKingCastleFile("../templates/black_king_castle.txt");
    blackKingCastleFile << 0;
    blackKingCastleFile.close();

    std::ofstream blackRightRookCastleFile("../templates/black_right_rook_castle.txt");
    blackRightRookCastleFile << 0;
    blackRightRookCastleFile.close();

    std::ofstream blackLeftRookCastleFile("../templates/black_left_rook_castle.txt");
    blackLeftRookCastleFile << 0;
    blackLeftRookCastleFile.close();

    std::ofstream checkFlagFile("../templates/check_flag.txt");
    checkFlagFile << 0 << ',' << 0;
    checkFlagFile.close();

    std::ofstream newStateFile("../templates/new_state.txt");
    newStateFile << 0;
    newStateFile.close();

    std::ofstream resignFile("../templates/resign.txt");
    resignFile << 0;
    resignFile.close();

    std::ofstream resignPopupFile("../templates/resign_popup.txt");
    resignPopupFile << 0;
    resignPopupFile.close();

    std::ofstream resignConfirmFile("../templates/resign_confirm.txt");
    resignConfirmFile << 0;
    resignConfirmFile.close();

    std::ofstream staleMateFile("../templates/stalemate.txt");
    staleMateFile << 0;
    staleMateFile.close();
}

void Game::initStates()
{
    this->stateStack.push(new MainMenuState(this->window));
}

Game::Game()
{
    this->initWindow();
    this->initApplication();
    this->initStates();
}

Game::~Game()
{
    while (!this->stateStack.empty())
    {
        delete this->stateStack.top();
        this->stateStack.pop();
    }

    delete this->window;
    this->window = nullptr;
}

void Game::updateDeltaTime()
{
    this->deltaTime = this->dtClock.restart().asSeconds();
}

void Game::updateWindow()
{
    while (this->window->pollEvent(this->e))
    {
        if (e.type == sf::Event::Closed)
        {
            this->window->close();
        }

        if (e.type == sf::Event::MouseButtonPressed)
        {
            std::ofstream mousePositionFile("../templates/mouse_position.txt");
            mousePositionFile << 1 << ',' << e.mouseButton.x << ',' << e.mouseButton.y << std::endl;
            mousePositionFile.close();
        }
    }

    if (!this->stateStack.empty())
    {
        this->stateStack.top()->update(this->deltaTime);

        bool newStateGen;
        std::ifstream newStateFile("../templates/new_state.txt");
        newStateFile >> newStateGen;
        newStateFile.close();

        if (newStateGen)
        {
            std::ofstream newStateFile_1("../templates/new_state.txt");
            newStateFile_1 << 0;
            newStateFile_1.close();

            this->stateStack.push(new MatchState(this->window));
        }

        bool exit;
        std::ifstream resignFile("../templates/resign.txt");
        resignFile >> exit;
        resignFile.close();
        if (exit)
        {
            initApplication();

            this->stateStack.push(new MainMenuState(this->window));
        }

        if (this->stateStack.top()->isStateQuit())
        {
            this->stateStack.top()->endState();
            delete this->stateStack.top();
            this->stateStack.pop();
            this->initApplication();
            this->window->close();
        }
    }
    else
    {
        this->window->close();
    }
}

void Game::renderWindow()
{
    this->window->clear();

    if (!this->stateStack.empty())
    {
        this->stateStack.top()->render();
    }

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->updateWindow();
        this->renderWindow();
    }
}