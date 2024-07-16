#pragma once

#include "Entity.h"

class State
{
private:

protected:
    sf::RenderWindow *window;
    std::vector<sf::Texture> textures;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

public:
    State(sf::RenderWindow *window);
    virtual ~State();

    const bool& getQuit() const;

    virtual void checkForQuit();

    virtual void endState() = 0;
    virtual void updateMousePositions();
    virtual void updateInput(const float& deltaTime) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf::RenderTarget *target = NULL) = 0;
};