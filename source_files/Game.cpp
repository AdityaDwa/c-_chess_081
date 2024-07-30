#include "../header_files/Game.h"

void Game::initWindow()
{
    // this->window = new sf::RenderWindow(sf::VideoMode(1728, 972), "Chess", sf::Style::Default);
    this->window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "Chess", sf::Style::Fullscreen);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(true);
}

void Game::initStates()
{
    this->stateStack.push(new MatchState(this->window));
}

Game::Game()
{
    this->initWindow();
    this->endApplication();
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
            endApplication();
            this->window->close();
        }

        if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::Escape)
            {
                endApplication();
                this->window->close();
            }
        }

        if (e.type == sf::Event::MouseButtonPressed)
        {
            std::ofstream test("../mouse_position.txt");
            test << 1 << ',' << e.mouseButton.x << ',' << e.mouseButton.y << std::endl;
            test.close();
        }
    }

    if (!this->stateStack.empty())
    {
        this->stateStack.top()->update(this->deltaTime);

        if (this->stateStack.top()->isStateQuit())
        {
            this->stateStack.top()->endState();
            delete this->stateStack.top();
            this->stateStack.pop();
        }
    }
    else
    {
        endApplication();
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

void Game::endApplication()
{
    std::ifstream sourceFile("../initial_position.txt");
    std::ofstream destinationFile("../pieces_info.txt");
    std::string line;

    while (std::getline(sourceFile, line))
    {
        destinationFile << line << std::endl;
    }

    sourceFile.close();
    destinationFile.close();

    std::ifstream inactiveFile("../inactive_all_tiles.txt");
    std::ofstream activeFile("../active_tiles.txt");
    std::string activeLine;

    while (std::getline(inactiveFile, activeLine))
    {
        activeFile << activeLine << std::endl;
    }

    inactiveFile.close();
    activeFile.close();

    std::ofstream vacancy("../isClickedOn.txt");
    vacancy.close();

    std::ofstream filler("../turn.txt");
    filler << 1;
    filler.close();

    std::ifstream winfile("../pieces_info.txt");
    std::ofstream woutfile("../ongoing_piece_info.txt");
    std::string wline;

    while (std::getline(winfile, wline))
    {
        woutfile << wline << std::endl;
    }
    winfile.close();
    woutfile.close();

    std::ofstream idk("../mouse_position.txt");
    idk << 0 << ',' << 0 << ',' << 0;
    idk.close();
}