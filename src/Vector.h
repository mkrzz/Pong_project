#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <SFML/Graphics.hpp>

class Vector
{
 private:
  float x; 
  float y;

  public:
  Vector(float x = 0.0f, float y = 0.0f);

  float getX() const;
  float getY() const;
  void setX(float x);
  void setY(float y);

  void normalise();
  Vector operator*(float scalar) const;

 

};







#endif VECTOR_H

