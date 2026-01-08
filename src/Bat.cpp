#include "Bat.h"
#include <iostream>
#include "Ball.h"
#include "Game.h"

Bat::Bat()
{

  texture.loadFromFile("../Data/Images/paddleBlue.png");
  sprite.setTexture(texture);
  sprite.setRotation(90);


}

void Bat::setPosition(float x, float y)
{
  sprite.setPosition(x, y);
}

void Bat::moveUp(float speed)
{
  //prevent moving above the screen
  if (sprite.getPosition().y > 0)
  {
    sprite.move(0, -speed);
  }
}

void Bat::moveDown(float speed, float windowHeight)
{
  //prevent moving below the screen
  if (sprite.getPosition().y + sprite.getGlobalBounds().height < windowHeight)
  {
    sprite.move(0, speed);
  }
}

void Bat::render(sf::RenderWindow& window)
{
  window.draw(sprite); //draw the bat sprite
}



sf::FloatRect Bat::getBounds() const
{
  return sprite.getGlobalBounds(); 
}
