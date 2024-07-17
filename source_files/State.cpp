#include "../header_files/State.h"

State::State(bool *toRender, sf::RenderWindow *window)
{
    this->window = window;
    this->quitState = false;
}

State::~State()
{
}

const bool &State::isStateQuit() const
{
    return this->quitState;
}

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}