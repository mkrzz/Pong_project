#include "Ball.h"
#include "Vector.h"
#include <iostream>



Ball::Ball()
{
  
  texture.loadFromFile("../Data/Images/ball.png");
  sprite.setTexture(texture);
  sprite.setScale(0.2f, 0.2f);
  sprite.setPosition(400, 300);         
  velocity = Vector(350.0f, -350.0f); 
}

void Ball::setVelocity(float x, float y)
{
  velocity.setX(x);
  velocity.setY(y);
}

Vector Ball::getVelocity() const
{
  return velocity; 
}

void Ball::render(sf::RenderWindow& window) 
{
  window.draw(sprite);
}


void Ball::handleCollisions(sf::RenderWindow& window)
{
  sf::FloatRect ballBounds = sprite.getGlobalBounds();
  sf::Vector2u windowSize  = window.getSize();

  //ball-wall collision
  if (ballBounds.top <= 0 || ballBounds.top + ballBounds.height >= windowSize.y)
  {
    velocity.setY(-velocity.getY()); 
  }
  if (ballBounds.left <= 0 || ballBounds.left + ballBounds.width >= windowSize.x)
  {
    velocity.setX(-velocity.getX()); 
  }
}

// mnove sprite based on velocity
void Ball::update(float dt)
{
  sprite.move(velocity.getX() * dt, velocity.getY() * dt);
}

//return bounds of ball
sf::FloatRect Ball::getBounds() const
{
  return sprite.getGlobalBounds();
}

void Ball::setPosition(float x, float y)
{
  sprite.setPosition(x, y);
}