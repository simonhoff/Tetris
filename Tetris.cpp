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
	delete[] board;
}

void Tetris::newTetromino(){
	delete current;
	//GENERATOR//
	/////////////
	current = next;
	next = generated;
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
	int boardX = current->getPosX();
	int boardY = current->getPosY();
	current->setPos(boardX, boardY - height());

	// Copy current into board
	for (int x = 0; x < current->getWidth; x++){
		for (int y = 0; y < current->getHeight(); y++){
			Field_t* temp = current->get(x,y);
			if (temp->occupied){
				(*(*(board + boardY + y) + boardX + x))->occupied = temp->occupied;
				(*(*(board + boardY + y) + boardX + x))->clr = temp->clr;
			}
		}
	}
	newTetromino();
}

/*********************************
* Returns shortest distance before
* the tetromino will be grounded, 
* in whole tiles
*********************************/
int Tetris::height(){
	int counter = 0;
	int position = current->getPosX();
	int mHeight = ROWS;
	for (int indX = position; indX < (position + current->getWidth()); indX++){
		int h = 0;
		int y = current->getPosY() + current->emptySpace(indX);
		while (!(*(*(board + y) + indX))->occupied){
			h++;
			y--;
		}
		if (h < mHeight) mHeight = h;
	}
	return mHeight;
}
