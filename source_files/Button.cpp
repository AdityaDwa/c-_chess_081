#include "../header_files/Button.h"

Button::Button(float x, float y, float width, float height, sf::Font *font, std::string innerText, sf::Color defaultColor, sf::Color focusedColor, std::string imagePath)
{
    this->hasImage = false;
    this->buttonShape.setPosition(sf::Vector2f(x, y));
    this->buttonShape.setSize(sf::Vector2f(width, height));
    this->buttonShape.setFillColor(this->defaultColor);

    if (!imagePath.empty() && this->texture.loadFromFile(imagePath)) {
        this->hasImage = true;
        this->texture.setSmooth(true);
        this->sprite.setTexture(this->texture);

        // Calculate scale factors
        float scaleX = width / this->sprite.getLocalBounds().width;
        float scaleY = height / this->sprite.getLocalBounds().height;

        // Set scale to fit the button
        this->sprite.setScale(scaleX, scaleY);
        this->sprite.setPosition(x, y);
    } else {
        this->font = font;
        this->innerText.setFont(*this->font);
        this->innerText.setString(innerText);
        this->innerText.setFillColor(sf::Color::White);
        this->innerText.setCharacterSize(24);
        this->innerText.setPosition(
            (this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->innerText.getGlobalBounds().width / 2.f),
            (this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->innerText.getGlobalBounds().height / 2.f)
        );
    }

    this->defaultColor = defaultColor;
    this->focusedColor = focusedColor;

}

Button::~Button()
{
}

void Button::update(const sf::Vector2f mousePos){
    this->buttonShape.setFillColor(this->defaultColor);

    this->isClicked = false;
    if (this->buttonShape.getGlobalBounds().contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->buttonShape.setFillColor(this->focusedColor);
            this->isClicked = true;
        }
        else {
            this->isClicked = false;
        }
        
    }
    
}

void Button::render(sf::RenderTarget *target) {
    target->draw(this->buttonShape);
    if (this->hasImage) {
        target->draw(this->sprite);
    }
    else {
        target->draw(this->innerText);
    }
}