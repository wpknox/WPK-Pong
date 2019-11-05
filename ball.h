#ifndef BALL_H
#define BALL_H

class ball
{
private:
	int x_pos;
	int y_pos;
	int x_speed;
	int y_speed;
public:
	ball(int init_x_speed, int init_y_speed);
	int get_x();
	int get_y();
	int get_x_speed();
	int get_y_speed();
	void set_x(int new_x);
	void set_y(int new_y);
	void set_x_speed(int new_x_speed);
	void set_y_speed(int new_y_speed);
};

#endif
