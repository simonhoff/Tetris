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
	current->move(dir);
}

void Tetris::rotate(){
	current->rotate();
}

void Tetris::softDrop(){

}

void Tetris::hardDrop(){

}
