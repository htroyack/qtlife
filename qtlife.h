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
  unsigned char board[50][50];
  unsigned char previous[50][50];
};

#endif  // __QTLIFE_BOARD_H

