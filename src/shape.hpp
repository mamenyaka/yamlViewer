#ifndef SHAPE_HPP
# define SHAPE_HPP

# include <string>

struct ShapeType
{
  enum value
  {
    Circle,
    Triangle,
    Rectangle
  };
};

class Shape
{
public:
  ShapeType::value type;
  std::string color;
};

class Triangle : public Shape
{
public:
  double a, b, c;
};

class Rectangle : public Shape
{
public:
  double length, width;
};

class Circle : public Shape
{
public:
  double radius;
};

#endif                                                      // SHAPE_HPP
