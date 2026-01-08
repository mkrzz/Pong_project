#pragma once
#ifndef BALL_H
#  define BALL_H
#  include <SFML/Graphics.hpp>
#include "Vector.h"

class Ball
{
 private:
  sf::Sprite sprite;
  sf::Texture texture;
  Vector velocity;


 public:
  Ball();
  void update(float dt);
  void render(sf::RenderWindow& window);
  void handleCollisions(sf::RenderWindow& window);
  void setVelocity(float x, float y);
  sf::FloatRect getBounds() const;
  Vector getVelocity() const;
  void setPosition(float x, float y);

};

#endif // BALL_H