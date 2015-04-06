#ifndef WIDGET_HPP
# define WIDGET_HPP

# include <QWidget>

# include <vector>

class Shape;

class Widget : public QWidget
{
  Q_OBJECT

  std::vector<Shape*> shapes;

  void parse_yaml();

public:
  explicit Widget(QWidget* parent = 0, Qt::WindowFlags f = 0);
  virtual ~Widget();

protected:
  void paintEvent(QPaintEvent* event);
};

#endif                                                      // WIDGET_HPP
