#include <QApplication>

#include "qtlife.h"

LifeBoard::LifeBoard(QWidget *parent)
  : QWidget(parent)
{
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(300);

  setWindowTitle(tr("Conway's Game of Life"));
  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      board[i][j] = 0;

  board[10][10] = 1;
  board[10][11] = 1;

  resize(500, 500);
}

int countNeighbours(unsigned char board[][50], int i, int j)
{
  int neighbours = 0;

  for (int x = i - 1; x <= i + 1; x++)
    for (int y = j - 1; y <= j + 1; y++)
    {
      if (x == i && y == j)
        continue;
      if (x < 0 || y < 0 || x >= 50 || y >= 50)
        continue;

      neighbours += board[x][y];
    }

  return neighbours;
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

  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      previous[i][j] = board[i][j];

  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
    {
      board[i][j] = 0;
      int neighbours = countNeighbours(previous, i, j);
      if (neighbours > 3 || neighbours < 2)
        continue;
      if (previous[i] || neighbours == 3)
        board[i][j] = 1;
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

