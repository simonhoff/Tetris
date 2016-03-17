#include <cstdlib>
#include <new>
#include "tetris.h"
#include "shape.h"

#define ROWS 20
#define COLS 10

using namespace std;


Tetris::Tetris(){
	rows = ROWS;
	cols = COLS;
	board = new Field_t*[rows];
	for (int row = 0; row < rows; row++ ){
		board[row] = new Field_t[cols]; 
	}
}

Tetris::~Tetris(){
	for (int row = 0; row < rows; row++){
		delete[] board[i];
	}
	delete[]
}

void Tetris::startGame(){

}

void Tetris::update(){

}

void Tetris::move(enum Direction dir){
	current->move();
}

void Tetris::rotate(){
	current->rotate();
}

void Tetris::hardDrop(){

}

int Tetris::height(){
	int counter = 0;
	int position = current->getPosX();
	int mHeight = 0;
	for (int indX = position; indX < (position + current->getWidth()); indX++){
		int h = 0;
		int y = current->getPosY() + current->emptySpace(indX);
		while (!(*(*(board + y) + indX))->occupied){
			h++;
			y--;
		}
		if (h > mHeight) mHeight = h;
	}
	return mHeight;
}
