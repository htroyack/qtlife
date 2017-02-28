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
  enum {WIDTH = 50, HEIGHT = 50, REFRESH = 100, CELLSIZE = 10};

  unsigned char current[WIDTH][HEIGHT];
  unsigned char previous[WIDTH][HEIGHT];

  QColor bgColor;
  QColor gridColor;
  QColor cellColor;
  
  int countNeighbours(int i, int j);
  void moveToNextGeneration();
  void addGliderGun();
  void drawBackground(QPainter& painter);
  void drawCells(QPainter& painter);
};

#endif  // __QTLIFE_BOARD_H

