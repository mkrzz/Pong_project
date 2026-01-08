#include "Vector.h"



//getters
float Vector::getX() const
{
  return x;
}
float Vector::getY() const
{
  return y;
}

Vector::Vector(float x, float y) : x(x), y(y) {}

//setters
void Vector::setX(float x)
{
  this->x = x;
}
void Vector::setY(float y)
{
  this->y = y;
}

//convert to unit vector
void Vector::normalise()
{
  float magnitude = std::sqrt(x * x + y * y);
  if (magnitude > 0.0f) 
  {
    x /= magnitude;
    y /= magnitude;
  }
}

//override operator symbol
Vector Vector::operator*(float scalar) const
{
  return Vector(x * scalar, y * scalar);
}