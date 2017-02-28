#include "lifeboard.h"

LifeBoard::LifeBoard(QWidget *parent)
  : QWidget(parent),
    bgColor(0, 0, 0), gridColor(0, 255, 0), cellColor(0, 255, 0)
{
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(REFRESH);

  setWindowTitle(tr("Conway's Game of Life"));

  // set all cells to initially dead
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < HEIGHT; j++)
      current[i][j] = 0;

  /*
   * current[10][10] = 1;
   * current[10][11] = 1;
   */

  // add a glider gun so our game don't start empty
  addGliderGun();
}

int LifeBoard::countNeighbours(int i, int j)
{
  int neighbours = 0;

  for (int x = i - 1; x <= i + 1; x++)
    for (int y = j - 1; y <= j + 1; y++)
    {
      if (x == i && y == j)
        continue;
      if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        continue;

      neighbours += previous[x][y];
    }

  return neighbours;
}

void LifeBoard::drawBackground(QPainter& painter)
{
  // fill background with solid color
  painter.setBrush(bgColor);
  painter.drawRect(0, 0, WIDTH*CELLSIZE, HEIGHT*CELLSIZE);

  // draw grid
  painter.setPen(gridColor);
  // horizontal lines
  for (int i = 0; i < HEIGHT; i++)
    painter.drawLine(0, i * CELLSIZE, CELLSIZE * HEIGHT, i * CELLSIZE);
  // vertical lines
  for (int i = 0; i < WIDTH; i++)
    painter.drawLine(i * CELLSIZE, 0, i * CELLSIZE, CELLSIZE * WIDTH);
}

void LifeBoard::moveToNextGeneration()
{
  // save board status as previous generation
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < HEIGHT; j++)
      previous[i][j] = current[i][j];

  // evaluate next generation based on the previous
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < HEIGHT; j++)
    {
      int neighbours = countNeighbours(i, j);
      if (previous[i][j] && neighbours < 2)
        current[i][j] = 0;
      if (previous[i][j] && (neighbours == 2 || neighbours == 3))
        current[i][j] = 1;
      if (previous[i] && neighbours > 3)
        current[i][j] = 0;
      if (!previous[i][j] && neighbours== 3)
        current[i][j] = 1;
    }
}

void LifeBoard::drawCells(QPainter& painter)
{
  painter.setBrush(cellColor);

  // draw rectangles representing the live cells
  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      if (current[i][j])
        painter.drawRect((CELLSIZE*i)+2, (CELLSIZE*j)+2, 6, 6);
}

void LifeBoard::paintEvent(QPaintEvent*)
{
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);

  moveToNextGeneration();
  
  drawBackground(painter);
  drawCells(painter);
  
  resize(WIDTH * CELLSIZE, HEIGHT * CELLSIZE);
}

// TODO: receber a posicao onde a glider gun deve entrar
void LifeBoard::addGliderGun()
{
  // FUCKING GLIDER GUN ENTERED BY HAND!!! OH YEAH!! SUCK SEYMOUR CRAY!!!
  current[26][2] =1;
  current[24][3] =current[26][3] =1;
  current[14][4] =current[15][4] =current[22][4]=current[23][4]=current[36][4]=current[37][4]=1;
  current[13][5] =current[17][5] =current[22][5]=current[23][5]=current[36][5]=current[37][5]=1;
  current[2] [6] =current[3] [6] =current[12][6]=current[18][6]=current[22][6]=current[23][6]=1;
  current[2] [7] =current[3] [7] =current[12][7]=current[16][7]=current[18][7]=current[19][7]=current[24][7]=current[26][7]=1;
  current[12][8] =current[18][8] =current[26][8]=1;
  current[13][9] =current[17][9] =1;
  current[14][10]=current[15][10]=1;
}

