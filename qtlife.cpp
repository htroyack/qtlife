#include <QApplication>

#include "lifeboard.h"

int main(int argc, char *argv[])
{
  QApplication life(argc, argv);

  LifeBoard board;
  board.show();
  
  return life.exec();
}

