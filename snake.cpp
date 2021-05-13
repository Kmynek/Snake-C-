#include "snake.h"
#include "winsys.h"
#include "screen.h"
#include <algorithm>
CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
 restart();
}
void CSnake::restart()
{
  score=0;
  menu=false;
  pause=false;
  snake.clear();
  snake.push_front(CPoint(18,10));
  snake.push_front(CPoint(19,10));
  snake.push_front(CPoint(20,10));
  Foodie();
}
void CSnake::paint()
{
 CFramedWindow::paint();
 gotoyx(geom.topleft.y,geom.topleft.x+2);
 printl("SCORE -------> %d",score);
 if(menu == true )
 {
   gotoyx(geom.topleft.y+4,geom.topleft.x+4);
   printl("strzaki - zmiana okna");

    gotoyx(geom.topleft.y+5,geom.topleft.x+4);
   printl("tab - zmiana okna");

 gotoyx(geom.topleft.y+6,geom.topleft.x+4);
   printl("h - help");

 gotoyx(geom.topleft.y+7,geom.topleft.x+4);
   printl("p - pause");

    gotoyx(geom.topleft.y+8,geom.topleft.x+4);
   printl("r - restart");


 }
 else
 {
   for(auto& iterator:snake)
   {
     gotoyx(geom.topleft.y+iterator.y,geom.topleft.x+iterator.x);
     if(iterator==snake.front())
     {
       printc(head);
     }
     else
     {
       printc(tail);
     }
     
   }
    if(!(food==0))
    {
      gotoyx(geom.topleft.y+food.y,geom.topleft.x+food.x);
      printc(food_x);

    }
   if(pause == true)
   {
     
     gotoyx(geom.topleft.y+geom.size.y/2-1,geom.topleft.x+geom.size.x/2 -6);
     printl("                  ");
     gotoyx(geom.topleft.y+geom.size.y/2,geom.topleft.x+geom.size.x/2 -6);
     printl("   GAME PAUSED    ");
     gotoyx(geom.topleft.y+geom.size.y/2+1,geom.topleft.x+geom.size.x/2 -6);
     printl("                  ");
   }
 }
 
}
CPoint CSnake::nextMove(const CPoint& p)
{
  CPoint next;
  int temp;
  switch(dir)
  {
    case UP:
    temp = p.y -1 ==0 ? this->geom.size.y -2 : p.y-1;    
      next = CPoint(p.x,temp);
      break;
      
    case DOWN:
      temp = (p.y % (this->geom.size.y -2))+1;
      next = CPoint(p.x,temp);
      break;

    case LEFT:
      temp = p.x -1 ==0 ? this->geom.size.x -2 : p.x-1;    
      next = CPoint(temp,p.y);
      break;

    case RIGHT:
    temp = (p.x % (this->geom.size.x -2))+1;
      next = CPoint(temp,p.y);
      break;


  }
  return next;
}
void CSnake::Foodie()
{
  
  bool temp=true;

  while(temp)
  {
    temp=false;
    int x = (rand()%(geom.size.x-2))+1;
    int y = (rand()%(geom.size.y-2))+1;

    food =CPoint(x,y);

    for(auto& i: snake)
    {
      if(food==i)
      {
        temp=true;
      }

    }
  }
  
}

bool CSnake::handleEvent(int key)
{

  ++tick;
  if(!(tick%((1000/20)/8)))//half_sec_event
  {
    CPoint new_head= nextMove(snake.front());
    snake.push_front(new_head);
    if(new_head==food)
    {
      score++;
      Foodie();
    }
    else snake.pop_back();
    
      auto it =find_if(snake.begin()+1,snake.end(),[new_head]
      (const CPoint &ref)-> bool{
        return ref == new_head;
      });
    
    
    if(it!=snake.end())
    {
      

      restart();
    }

     return true;
  }
  

  if (CFramedWindow::handleEvent(key)==true)return true;


  switch (key)
  {
    case 'h':
      if(!pause)menu=! menu;
      return true;
    
    case 'p':
      if(!menu)pause=!pause;
      return true;

    case 'r':
      restart();
      return true;

    case 'w':
      if(dir!=DOWN)dir= UP;
      return true;
    case 'a':
     if(dir!=RIGHT) dir = LEFT;
      return true;
    case 's':
      if(dir!=UP)dir = DOWN;
      return true;
    case 'd':
      if(dir!=LEFT)dir = RIGHT;
      return true;
    
  }
  return false;
}