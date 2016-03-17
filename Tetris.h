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
	~Tetris();
	void startGame();
	void newTetromino();
	void update();
	void move(enum Direction dir);
	void rotate();
	void hardDrop();
	int height();

};