#include <cstdlib>
#include "paddle.h"

paddle::paddle(int player_num)
{
	if (player_num == 1)
	  x_pos = 9;
	else
	  x_pos = 70;
	y_pos = 9;
	size = 6;
	score = 0;
}

int paddle::get_x_pos()
{
  return x_pos;
}

int paddle::get_y_pos()
{
  return y_pos;
}

int paddle::get_size()
{
  return size;
}

int paddle::get_score()
{
  return score;
}

void paddle::set_score(int new_score)
{
  score = new_score;
}

void paddle::move_paddle(int y)
{
  y_pos = y;
}
