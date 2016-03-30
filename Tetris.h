#pragma once

#include "shape.h"

class Tetris{
private:
	Field_t ***board;
	int rows;
	int cols;
	Shape* current;
	Shape* next;
	std::vector<Shape*> queue;
	std::vector<Shape*>::iterator position;
public:
	Tetris();
	~Tetris();
	void startGame();
	void newTetromino();
	void generateQueue();
	void update();
	bool isRowFull(int y);
	void removeRows(int rowsA[]);
	void move(enum Direction dir);
	void rotate();
	void hardDrop();
	int height();
	bool isOccupied(int x, int y);
	Field_t* get(int x, int y);
};