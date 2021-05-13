#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <deque>
class CSnake:public CFramedWindow
{
public:
  CSnake(CRect r, char _c = ' ');
  deque<CPoint> snake;
  enum direction {UP,DOWN,LEFT,RIGHT} dir=UP;

  char head='@';
  char tail='+';
  bool menu;
  char food_x = 'x';
  unsigned int len;
  unsigned int score;
  int to;
  int pause;
  CPoint food;
  
  

  unsigned int tick =0;
  CPoint nextMove(const CPoint& p);
  void Foodie();
  void paint();
  void move();
  void restart();
  bool handleEvent(int key);

};

#endif
