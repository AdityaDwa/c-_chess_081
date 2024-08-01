#include "../header_files/MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow *window) : State(window)
{
    this->stateBackground.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->stateBackground.setFillColor(sf::Color(54, 58, 55));
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update(const float &deltaTime)
{
}

void MainMenuState::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }

    target->draw(this->stateBackground);
    this->renderBtns(target);
}

void MainMenuState::endState()
{
}

void MainMenuState::renderBtns(sf::RenderTarget *target)
{
    sf::RectangleShape btnBox[2];

    sf::Font btnFont;
    sf::Text btnText[2];
    sf::Text title;

    float startXPosition = (target->getSize().x - 225.f) / 2;
    float startYPosition = (target->getSize().y - 75.f) / 2;

    btnBox[0].setPosition(sf::Vector2f(startXPosition, startYPosition));
    btnBox[0].setSize(sf::Vector2f(225.f, 75.f));
    btnBox[0].setFillColor(sf::Color(169, 169, 169));

    target->draw(btnBox[0]);

    btnFont.loadFromFile("../fonts/inter_bold.ttf");
    btnText[0].setFont(btnFont);
    btnText[1].setFont(btnFont);

    title.setFont(btnFont);
    title.setString("Chess Game");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setPosition(sf::Vector2f((target->getSize().x / 2) - 300.f, 100.f));
    target->draw(title);

    btnText[0].setString("Play");
    btnText[0].setCharacterSize(30);
    btnText[0].setFillColor(sf::Color::White);

    btnText[0].setPosition(sf::Vector2f(startXPosition + 80.f, startYPosition + 20.f));
    target->draw(btnText[0]);

    btnBox[1].setPosition(sf::Vector2f(startXPosition, startYPosition + 125.f));
    btnBox[1].setSize(sf::Vector2f(225.f, 75.f));
    btnBox[1].setFillColor(sf::Color(169, 169, 169));

    target->draw(btnBox[1]);

    btnText[1].setString("Quit");
    btnText[1].setCharacterSize(30);
    btnText[1].setFillColor(sf::Color::White);

    btnText[1].setPosition(sf::Vector2f(startXPosition + 80.f, startYPosition + 145.f));
    target->draw(btnText[1]);

    bool clicked;
    char del1, del2;
    float mouseX, mouseY;

    std::ifstream mousePositionFile("../templates/mouse_position.txt");
    mousePositionFile >> clicked >> del1 >> mouseX >> del2 >> mouseY;
    mousePositionFile.close();

    sf::Vector2f clickPosition(mouseX, mouseY);

    if (clicked)
    {
        if (btnBox[0].getGlobalBounds().contains(clickPosition))
        {
            std::ofstream mousePositionFile_1("../templates/mouse_position.txt");
            mousePositionFile_1 << 0 << ',' << 0 << ',' << 0;
            mousePositionFile_1.close();

            std::ofstream newStateFile("../templates/new_state.txt");
            newStateFile << 1;
            newStateFile.close();
        }

        if (btnBox[1].getGlobalBounds().contains(clickPosition))
        {
            this->quitState = true;
        }
    }
}