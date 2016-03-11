#pragma once

#include "shape.h"

class Tetris{
private:
	Field_t **board;
	int rows;
	int cols;
	Shape* current;
	Shape* next;
public:
	Tetris();
	void startGame();
	void update();
	void move(enum Direction dir);
	void rotate();
	void softDrop();
	void hardDrop();

};