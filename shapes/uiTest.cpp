/****************************************
 * UI TEST
 * Just a simple program to test the user
 * interface consisting of uiDraw and uiInteract
 ***************************************/


#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
using namespace std;



#define MAX_SIDES 8
#define MIN_SIDES 2
#define MAX_X 500
#define MIN_X -500
#define MAX_Y 500
#define MIN_Y -500


/************************************
 * Test structure to capture the ball
 * that I will move around the screen
 ***********************************/
class Ball
{
public:

  // this is just for test purposes.  Don't make member variables public!
  Point pt;
  Point pt2;// location of the polygon on the screen
  int sides = 5;         // number of sides in the polygon.  Initially three
  int rotation;// the angle or orientation of the polygon
  int x_vel = 0;
  int x_vel2 = 0;
  int y_vel = 0;
  int y_vel2 = 0;
  int rpm = 1;
  int stride = 30;
  int accel = 2;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void * p)
{
  Ball * pBall = (Ball *)p;
  //Ball * lBall = (Ball *)l;
  if (pUI->isRight())
    {
      pBall->pt.addX(pBall->stride);
      pBall->x_vel += pBall->accel;
    }
  if(pBall->pt.getX() > MAX_X)
	pBall->pt.setX(MIN_X);
  if (pUI->isLeft())
    {
      pBall->pt.addX(-pBall->stride);
      pBall->x_vel -= pBall->accel;
    }
  if (pBall->pt.getX() < MIN_X)
    pBall->pt.setX(MAX_X);
  if (pUI->isUp())
    {
      pBall->pt.addY(pBall->stride);
      pBall->y_vel += pBall->accel;
    }
  if (pBall->pt.getY() > MAX_Y)
    pBall->pt.setY(MIN_Y);
  if (pUI->isDown())
    {
      pBall->pt.addY(-pBall->stride);
      pBall->y_vel -= pBall->accel;
    }
  if (pBall->pt.getY() < MIN_Y)
    pBall->pt.setY(MAX_Y);
  pBall->pt.addX(pBall->x_vel);
  pBall->pt.addY(pBall->y_vel);
  if (pBall->x_vel > 0)
    pBall->x_vel--;
  else if (pBall->x_vel < 0)
    pBall->x_vel++;
  else
    cout << "";
  if (pBall->y_vel > 0)
    pBall->y_vel--;
  else if (pBall->y_vel < 0)
    pBall->y_vel++;
  else
    cout << "";
  if (pUI->isSpace())
    {
      pBall->sides += 1;
      pBall->rpm = -(pBall->rpm);
    }
  if (pBall->sides > MAX_SIDES)
    pBall->sides = MIN_SIDES;
  pBall->rotation++;
  drawPolygon(pBall->pt, 10, pBall->sides, (16 * pBall->rpm) * (pBall->rotation));
  drawPolygon(pBall->pt, 20, pBall->sides, (8 * pBall->rpm) * (pBall->rotation));
  drawPolygon(pBall->pt, 40, pBall->sides, (4 * pBall->rpm) * (pBall->rotation));
  drawPolygon(pBall->pt, 80, pBall->sides, (2 * pBall->rpm) * (pBall->rotation));
  /*  if (pUI->isD())
    {
      pBall->pt2.addX(stride);
      pBall->x_vel2 += 2;
    }
  if(pBall->pt2.getX() > MAX_X)
    pBall->pt2.setX(MIN_X);
  if (pUI->isA())
    {
      pBall->pt2.addX(-stride);
      pBall->x_vel2 -= 2;
    }
  if (pBall->pt2.getX() < MIN_X)
    pBall->pt2.setX(MAX_X);
  if (pUI->isW())
    {
      pBall->pt2.addY(stride);
      pBall->y_vel2 += 2;
    }
  if (pBall->pt2.getY() > MAX_Y)
    pBall->pt2.setY(MIN_Y);
  if (pUI->isS())
    {
      pBall->pt2.addY(-stride);
      pBall->y_vel2 += 2;
    }
  if (pBall->pt2.getY() < MIN_Y)
    pBall->pt2.setY(MAX_Y);
  pBall->pt2.addX(pBall->x_vel2);
  pBall->pt2.addY(pBall->y_vel2);
  if (pBall->x_vel2 > 0)
    pBall->x_vel2--;
  else if (pBall->x_vel2 < 0)
    pBall->x_vel2++;
  else
    cout << "";
  if (pBall->y_vel2 > 0)
    pBall->y_vel2--;
  else if (pBall->y_vel2 < 0)
    pBall->y_vel2++;
  else
    cout << "";
  drawPolygon(pBall->pt2, 10, pBall->sides, (16 * pBall->rpm) * (pBall->rotation));
  drawPolygon(pBall->pt2, 20, pBall->sides, (8 * pBall->rpm) * (pBall->rotation));
  drawPolygon(pBall->pt2, 40, pBall->sides, (4 * pBall->rpm) * (pBall->rotation));
  drawPolygon(pBall->pt2, 80, pBall->sides, (2 * pBall->rpm) * (pBall->rotation));
  */
  if (pUI->isQ())
    exit(0);
  if (pUI->isS())
    pBall->rpm = -(pBall->rpm);
  if (pUI->isT() && pBall->stride == 30)
    {
      pBall->stride = 1;
      pBall->accel = 5;
    }
  else if (pUI->isT() && pBall->stride == 1)
    {
      pBall->stride = 30;
      pBall->accel = 2;
    }
  else
    cout << "";
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my ball type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
  Interface ui(argc, argv, "Test", Point(-MAX_Y, MAX_Y), Point(MAX_X, -MAX_X));    // initialize OpenGL
  Ball ball;// initialize the game state
  //  Ball ball2;
  ui.run(callBack, &ball);             // set everything into action

  return 0;
}
