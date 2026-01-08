#pragma once
#ifndef BAT_H

#define BAT_H
#include <SFML/Graphics.hpp>

class Bat
{

  private:
  sf::Sprite sprite;
  sf::Texture texture;

  public:
  Bat();
  void render(sf::RenderWindow& window);
  void moveUp(float speed);                       
  void moveDown(float speed, float windowHeight); 
  sf::FloatRect getBounds() const;
  void setPosition(float x, float y);

};






























#endif