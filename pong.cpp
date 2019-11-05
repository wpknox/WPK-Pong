#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <ctime>

#include "paddle.h"
#include "ball.h"

#define MIN_X_SPEED		 1
#define MIN_Y_SPEED              0
#define MAX_Y_SPEED              1
#define LEFT_X			 9
#define RIGHT_X			70
#define PADDLE_Y_START           9 
#define PONG_Y_MIN               1
#define PONG_Y_MAX              18
#define PONG_BALL_MIN            1
#define PONG_BALL_MAX           23
#define FIRST_PLAYER             1
#define SECOND_PLAYER            2
#define BALL_X                  39
#define BALL_Y                  11
#define REFRESH_RATE            60000
#define NO_Y_REFRESH            45000
#define SCORE_LIMIT             10


void init_ncurses();
void start_screen();
void end_game_screen(paddle *p1, paddle *p2);
void draw_paddle(paddle *p);
void draw_ball(ball *b);
void draw_score(paddle *p);
void draw_board(paddle *p1, paddle *p2, ball *b);
void play_game(paddle *p1, paddle *p2, ball *b);
bool hit_paddle(ball *b, paddle *p);
bool hit_wall(ball *b);
bool past_paddle(ball *b, paddle *p1, paddle *p2);
bool score_check(paddle *p1, paddle *p2);
void reset();

int main(int argc, char *argv[])
{
  srand(time(NULL));
  init_ncurses();
  paddle player_one(FIRST_PLAYER);
  paddle player_two(SECOND_PLAYER);
  ball ball(MIN_X_SPEED, MIN_Y_SPEED);
  start_screen();
  play_game(&player_one, &player_two, &ball);
  end_game_screen(&player_one, &player_two);
  endwin();
  return 0;
}

void init_ncurses()
{
  initscr();
  raw();
  noecho();
  curs_set(0);
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
}

void start_screen()
{
  clear();
  mvprintw(3, 32, "Made by Willis Knox");
  mvprintw(8, 29, "Welcome to my Pong game!");
  mvprintw(10, 13, "Two people play each other until someone gets 10 points");
  mvprintw(12, 2, "Player One uses 'w' and 's' to move");
  mvprintw(12, 42, "Player Two uses 'i' and 'k' to move");
  mvprintw(14, 26, "Press 'q' to quit at any time");
  mvprintw(16, 30, "Press any key to start");
  refresh();
  while(getch() == ERR);
}

void end_game_screen(paddle *p1, paddle *p2)
{
  clear();
  if(p1->get_score() >= SCORE_LIMIT)
    mvprintw(9, 18, "Congratulations Player One, you won the game!");
  else if(p2->get_score() >= SCORE_LIMIT)
    mvprintw(9, 18, "Congratulations Player Two, you won the game!");
  else
    mvprintw(9, 28, "The game ended in a draw!");
  mvprintw(13, 25, "Press any key to exit the game");
  refresh();
  while(getch() == ERR);
}

void draw_ball(ball *b)
{
  mvprintw(b->get_y(), b->get_x(), "O");
}

void draw_paddle(paddle *p)
{
  int i;
  for (i = 0; i < p->get_size(); i++)
    {
      mvprintw(p->get_y_pos() + i, p->get_x_pos(), "|");
    }
}

void draw_score(paddle *p)
{
  mvprintw(0, p->get_x_pos() - 4, "Score: %d", p->get_score());
}

void draw_board(paddle *p1, paddle *p2, ball *b)
{
  clear();
  draw_ball(b);
  draw_paddle(p1);
  draw_paddle(p2);
  draw_score(p1);
  draw_score(p2);
  refresh();
}

bool hit_paddle(ball *b, paddle *p)
{
  if(b->get_x() == p->get_x_pos())
    {
      return ((b->get_y() >= p->get_y_pos()) && (b->get_y() < p->get_y_pos() + p->get_size()));
    }
  else
    {
      return false;
    }
}

bool hit_wall(ball *b)
{
  return b->get_y() <= PONG_BALL_MIN || b->get_y() >= PONG_BALL_MAX;
}

bool past_paddle(ball *b, paddle *p1, paddle *p2)
{
  if(b->get_x() < 1)
    {
      p2->set_score(p2->get_score() + 1);
      return true;
    }
  if(b->get_x() > 78)
    {
      p1->set_score(p1->get_score() + 1);
      return true;
    }
  return false;
}

void reset(ball *b, paddle *p1, paddle *p2)
{
  clear();
  p1->move_paddle(PADDLE_Y_START);
  p2->move_paddle(PADDLE_Y_START);
  b->set_x(BALL_X);
  b->set_y(BALL_Y);
  b->set_x_speed(b->get_x_speed() * -1);
  b->set_y_speed(MIN_Y_SPEED);
  refresh();
  usleep(REFRESH_RATE * 10);
}

bool score_check(paddle *p1, paddle *p2)
{
  return p1->get_score() >= SCORE_LIMIT || p2->get_score() >= SCORE_LIMIT;
}

void play_game(paddle *p1, paddle *p2, ball *b)
{
  int running = 1;
  char key;
  while(running)
    {
      key = getch();
      while (key == ERR)
	{
	  key = getch();
	  draw_board(p1, p2, b);
	  if(b->get_y_speed() == MIN_Y_SPEED)
	    usleep(NO_Y_REFRESH);
	  else
	    usleep(REFRESH_RATE);
	  b->set_x(b->get_x() + b->get_x_speed());
	  b->set_y(b->get_y() + b->get_y_speed());
	  if(hit_wall(b))
	    {
	      b->set_y_speed(b->get_y_speed() * -1);
	    }
	  if(hit_paddle(b, p1) || hit_paddle(b, p2))
	    {
	      b->set_x_speed(b->get_x_speed() * -1);
	      int temp = rand() % 17;
	      if(temp == 0)
		b->set_y_speed(MIN_Y_SPEED);
	      else if (temp == 4 || temp == 13 || temp == 9)
		b->set_y_speed(b->get_y_speed() * -1);
	      else
		b->set_y_speed(MAX_Y_SPEED);
	    }
	  if(past_paddle(b, p1, p2))
	    {
	      if(score_check(p1, p2))
		{
		  running = 0;
		  break;
		}
	      reset(b, p1, p2);
	      break;
	    }
	  if(key != ERR)
	    {
	      ungetch(key);
	      break;
	    }
	}

      key = getch();

      switch(key)
	{
	case 'w':
	  if(p1->get_y_pos() > PONG_Y_MIN)
	    {
	      p1->move_paddle(p1->get_y_pos() - 1);
	    }
	  break;
	case 's':
	  if(p1->get_y_pos() < PONG_Y_MAX)
	    {
	      p1->move_paddle(p1->get_y_pos() + 1);
	    }
	  break;
	case 'i':
	  if(p2->get_y_pos() > PONG_Y_MIN)
	    {
	      p2->move_paddle(p2->get_y_pos() - 1);
	    }
	  break;
	case 'k':
	  if(p2->get_y_pos() < PONG_Y_MAX)
	    {
	      p2->move_paddle(p2->get_y_pos() + 1);
	    }
	  break;
	case 'q':
	  running = 0;
	  break;
	}
    }
  return;
}
