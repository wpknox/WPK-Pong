# WPK-Pong
## C++ Pong Made for CS 327 Assignment

For our last weekly programming assignment in Com Sci 327, we were given the option to create our own game in C++. I decided to make a simple Pong game that uses the **ncurses** library to display the playing board.

There are two players. Player one controls the left paddle and player two controls the right paddle.

Player one uses **w** and **s** to move their paddle.

Player two uses **i** and **k** to move their paddle.

Either player can press 'q' to quit the game at any time. Otherwise, the game ends if either of the players reaches 10 points.

The paddles are made in paddle.h and paddle.cpp and the ball is made in ball.h and ball.cpp.

The main file where the game runs is **pong.cpp**

___

To run, simply download the files, go into the directory where they are stored, run **make** to compile your files, and then type **./pong** to play the game.

If you want to clean your directory, simply run **make clean**.

This is assuming that you have **g++**, **make**, and **ncurses** installed on your system.

___

**NOTE:** This project was programmed in a Slackware Linux VM given to me for this class. I do not guarantee that this will run on your machine.
