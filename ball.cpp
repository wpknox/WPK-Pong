#include <cstdlib>
#include "ball.h"

ball::ball(int init_x_speed, int init_y_speed)
{
	x_pos = 39;
	y_pos = 11;
	x_speed = init_x_speed;
	y_speed = init_y_speed;
}

int ball::get_x()
{
  return x_pos;
}

int ball::get_y()
{
  return y_pos;
}

int ball::get_x_speed()
{
  return x_speed;
}

int ball::get_y_speed()
{
  return y_speed;
}

void ball::set_x(int new_x)
{
  x_pos = new_x;
}

void ball::set_y(int new_y)
{
  y_pos = new_y;
}

void ball::set_x_speed(int new_x_speed)
{
  x_speed = new_x_speed;
}

void ball::set_y_speed(int new_y_speed)
{
  y_speed = new_y_speed;
}
