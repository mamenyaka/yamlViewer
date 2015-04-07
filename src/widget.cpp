#include "widget.hpp"
#include "shape.hpp"

#include <QPaintEvent>
#include <QPainter>

#include <yaml-cpp/yaml.h>

#include <map>

Widget::Widget(QWidget* parent, Qt::WindowFlags f): QWidget(parent, f)
{
  parse_yaml();
}

Widget::~Widget()
{
  for (const Shape* shape : shapes)
    delete shape;
}

void Widget::parse_yaml()
{
  std::map<std::string, ShapeType::value> shape_map;
  shape_map["circle"] = ShapeType::Circle;
  shape_map["rectangle"] = ShapeType::Rectangle;
  shape_map["triangle"] = ShapeType::Triangle;

  YAML::Node shapes = YAML::LoadFile("shapes.yaml");
  for (YAML::const_iterator it = shapes.begin(); it != shapes.end(); ++it)
  {
    const YAML::Node& node = *it;
    const YAML::Node& properties = node["properties"];

    const std::string str = node["shape"].as<std::string>();
    const std::string color = properties["color"].as<std::string>();

    const ShapeType::value type = shape_map[str];

    Shape* shape;
    if (type == ShapeType::Circle)
    {
      Circle* circle = new Circle;
      circle->radius = properties["radius"].as<double>();
      shape = circle;
    }
    if (type == ShapeType::Rectangle)
    {
      Rectangle* rect = new Rectangle;
      rect->length = properties["length"].as<double>();
      rect->width = properties["width"].as<double>();
      shape = rect;
    }
    if (type == ShapeType::Triangle)
    {
      Triangle* triangle = new Triangle;
      triangle->a = properties["a"].as<double>();
      triangle->b = properties["b"].as<double>();
      triangle->c = properties["c"].as<double>();
      shape = triangle;
    }

    shape->type = type;
    shape->color = color;
    this->shapes.push_back(shape);
  }
}

void Widget::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  int X = 20, Y = 20;
  for (const Shape* shape : shapes)
  {
    painter.setBrush(QBrush(QColor(QString::fromStdString(shape->color))));

    if (shape->type == ShapeType::Circle)
    {
      const Circle* circle = static_cast<const Circle*>(shape);
      const int diam = 2*circle->radius;

      painter.drawEllipse(X, Y, diam, diam);

      X += diam + 50;
    }
    if (shape->type == ShapeType::Rectangle)
    {
      const Rectangle* rect = static_cast<const Rectangle*>(shape);

      painter.drawRect(X, Y, rect->length, rect->width);

      X += rect->length + 50;
    }
    if (shape->type == ShapeType::Triangle)
    {
      const Triangle* triangle = static_cast<const Triangle*>(shape);

      std::vector<double> tmp;
      tmp.push_back(triangle->a);
      tmp.push_back(triangle->b);
      tmp.push_back(triangle->c);
      std::sort(tmp.begin(), tmp.end(), std::greater<double>());

      double a, b, c;
      a = tmp.at(0);
      b = tmp.at(1);
      c = tmp.at(2);

      double x, y;
      x = (c*c + a*a - b*b)/(2.0*a);
      y = std::sqrt(c*c - x*x);

      QPainterPath path;
      path.moveTo(X + 0, Y + y);
      path.lineTo(X + a, Y + y);
      path.lineTo(X + x, Y + 0);
      path.lineTo(X + 0, Y + y);

      painter.fillPath(path, painter.brush());

      X += a + 50;
    }
  }

  painter.end();
}
