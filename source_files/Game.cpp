#include "../header_files/Game.h"

void Game::initWindow(){
    //WINDOW RENDERING AND FRAME RATE SET
    this->window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "B-chess", sf::Style::Fullscreen);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initStates(){
    //STATES GENERATION
    this->states.push(new MainMenuState(this->window));
}

Game::Game(){
    //CALLING WINDOW INITIALIZER
    this->initWindow();
    this->initStates();
}

Game::~Game(){
    //DELETING MEMORY ALLOCATED BY GAME OBJECT
    delete this->window;
    this->window = nullptr;
    
    while (!this->states.empty())
    {
        delete this->states.top();      //DELETES THE ACTUAL DATA OF THE POINTER
        this->states.pop();             //DELETES THE POINTER
    }
    
}

void Game::endApplication(){
    std::cout<< "ending application";//remove later
}

void Game::toggleFullScreen() {
    static bool isFullScreen = true;

    if (isFullScreen) {
        //SWITCH TO WINDOWED MODE
        this->window->create(sf::VideoMode(1440, 810), "B-chess");
        isFullScreen = false;
    }
    else {
        //SWITCH TO FULLSCREEN MODE
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        this->window->create(desktop, "B-chess", sf::Style::Fullscreen);
        isFullScreen = true;
    }
}

void Game::updateDeltaTime(){
    //GETS DELTA TIME IN SECONDS
    this->deltaTime = this->dtClock.restart().asSeconds();
    // std::cout << this->deltaTime << std::endl; remove later
}

void Game::updateWindow(){
    //GAME RUNS UNTIL WINDOW IS CLOSED
    while (this->window->pollEvent(this->e)) {
        switch (e.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        //CHECKING KEYBIND TO TOGGLE FULLSCREEN
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Escape) {
                toggleFullScreen();
            }
            break;
        default:
            break;
        }
    }

    if (!this->states.empty()) {
        this->states.top()->update(this->deltaTime);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
        //END OF APPLICATION
    }
    else {
        endApplication();
        // this->window->close();
        
    }
}

void Game::renderWindow(){
    //CLEARING PREVIOUS WINDOW FRAME
    this->window->clear();

    if (!this->states.empty())
    {
        this->states.top()->render();
    }
    
    this->window->display();
}

void Game::run(){
    //GAME LOOP FUNCTION UNTIL IT IS CLOSED
    while (this->window->isOpen()) {
        this->updateDeltaTime();
        this->updateWindow();
        // sf::Vector2u windowSize = this->window->getSize();
        // sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        // bool isFullScreen =  (windowSize.x == desktopMode.width && windowSize.y == desktopMode.height);
        this->renderWindow();
    }
}