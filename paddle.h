#ifndef PADDLE_H
#define PADDLE_H

class paddle
{
private:
	int x_pos;
	int y_pos;
	int size;
	int score;
public:
	paddle(int player_num);
	int get_x_pos();
	int get_y_pos();
	int get_size();
	int get_score();
	void set_score(int new_score);
	void move_paddle(int y);
};

#endif
