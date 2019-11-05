all: ball.cpp paddle.cpp pong.cpp
	g++ -Wall -Werror -ggdb3 ball.cpp paddle.cpp pong.cpp -lncurses -o pong

clean:
	rm -f pong *~
