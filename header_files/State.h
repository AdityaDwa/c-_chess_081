#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
private:

protected:
    sf::RenderWindow *window;
    sf::RectangleShape stateBackground;
    bool quitState;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

public:
    State(sf::RenderWindow *window);
    virtual ~State();

    const bool& isStateQuit() const;
    virtual void updateMousePositions();

    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
    virtual void endState() = 0;
};