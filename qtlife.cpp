#include <QApplication>

#include "qtlife.h"

LifeBoard::LifeBoard(QWidget *parent)
  : QWidget(parent)
{
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(1000);

  setWindowTitle(tr("Conway's Game of Life"));
  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      board[i][j] = 0;

  board[10][10] = 1;

  resize(500, 500);
}

void LifeBoard::paintEvent(QPaintEvent *event)
{
  QColor gridColor(0,255, 0);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(gridColor);
  painter.setBrush(QColor(0, 0, 0));
  painter.drawRect(0, 0, 500, 500);
  for (int i = 0; i < 50; i++)
  {
    painter.drawLine(0, i * 10, 500, i * 10);
    painter.drawLine(i * 10, 0, i * 10, 500);
  }

  painter.setBrush(gridColor);
  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      if (board[i][j])
        painter.drawRect((10*i)+2, (10*j)+2, 6, 6);
}

int main(int argc, char *argv[])
{
  QApplication life(argc, argv);

  LifeBoard board;
  board.show();
  
  return life.exec();
}

