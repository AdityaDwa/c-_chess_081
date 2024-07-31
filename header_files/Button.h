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
#include <filesystem>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Button
{
private:

protected:
    int selfRow, selfColumn;
    int parentRow, parentColumn;

    float xPosition;
    float yPosition;

    sf::Texture texture;
    sf::Sprite sprite;

public:
    Button(int row, int column, int parentRow, int parentColumn, bool parentColor, sf::RenderTarget *target);
    virtual ~Button();

    void update();
    void render(sf::RenderTarget *target);
};