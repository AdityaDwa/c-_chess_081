#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Entity
{
private:

protected:
    sf::CircleShape shape;
    float movementSpeed;
    
public:
    Entity();
    virtual ~Entity();

    virtual void move(const float &deltaTime, const float x, const float y);
    virtual void update(const float& deltaTime);
    virtual void render(sf::RenderTarget *target);
};
