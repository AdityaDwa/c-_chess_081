#include "../header_files/MatchState.h"

MatchState::MatchState(bool *toRender, sf::RenderWindow *window) : State(toRender, window)
{
    this->stateBackground.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->stateBackground.setFillColor(sf::Color(119, 149, 86));
}

MatchState::~MatchState()
{
    // auto btnPair = this->btns.begin();
    // for (btnPair = this->btns.begin(); btnPair != this->btns.end(); ++btnPair)
    // {
    //     delete btnPair->second;
    // }
}

void MatchState::updateMousePositions()
{
}

void MatchState::updateInput(const float &deltaTime)
{
}

void MatchState::update(const float &deltaTime)
{
}

void MatchState::render(bool *toRender, sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }

    if (*toRender)
    {

        target->draw(this->stateBackground);

        this->gameBoard.render(toRender, target);

        *toRender = false;
    }
}

void MatchState::endState()
{
}