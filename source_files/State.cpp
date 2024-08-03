#include "../header_files/State.h"

State::State(sf::RenderWindow *window)
{
    // CLASS VARIABLES ARE INITIALIZED
    this->window = window;
    this->quitState = false;
}

State::~State()
{
}

const bool &State::isStateQuit() const
{
    // RETURNS THE BOOLEAN VALUE OF QUITSTATE
    return this->quitState;
}

// METHOD TO UPDATE MOUSE POSITION IN THE STATE WINDOW
void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}