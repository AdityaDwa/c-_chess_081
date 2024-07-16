#include "../header_files/Entity.h"

Entity::Entity()
{
    this->shape.setRadius(60.f);
    this->shape.setFillColor(sf::Color(119, 149, 86));
    this->movementSpeed = 500.f;
}

Entity::~Entity()
{
}

void Entity::move(const float &deltaTime, const float x, const float y){
    this->shape.move(x * this->movementSpeed * deltaTime, y * this->movementSpeed * deltaTime);
}

void Entity::update(const float &deltaTime){
}

void Entity::render(sf::RenderTarget *target){
    target->draw(this->shape);
}