#ifndef __QTLIFE_BOARD_H
#define __QTLIFE_BOARD_H

#include <QtWidgets>

class LifeBoard : public QWidget
{
  Q_OBJECT

public:
  LifeBoard(QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  enum {WIDTH = 50, HEIGHT = 50, REFRESH = 100, CELL = 10};
  unsigned char current[WIDTH][HEIGHT];
  unsigned char previous[WIDTH][HEIGHT];
  int countNeighbours(int i, int j);
};

#endif  // __QTLIFE_BOARD_H

