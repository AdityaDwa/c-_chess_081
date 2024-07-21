#include "../header_files/Game.h"

void Game::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    this->window = new sf::RenderWindow(sf::VideoMode(1440, 810), "Chess", sf::Style::Default, settings);
    // this->window = new sf::RenderWindow(sf::VideoMode(1440, 810), "Chess", sf::Style::Titlebar | sf::Style::Close);
    // this->window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "Chess", sf::Style::Fullscreen, settings);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initStates()
{
    this->stateStack.push(new MatchState(this->window));
}

Game::Game()
{
    this->initWindow();
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
    //////
    this->window->close();
}