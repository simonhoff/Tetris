#include <cstdlib>
#include <new>
#include <vector>
#include "Tetris.h"
#include "shape.h"

#define ROWS 20
#define COLS 10

using namespace std;


Tetris::Tetris(){
	rows = ROWS;
	cols = COLS;
	board = new Field_t*[rows];
	for (int row = 0; row < rows; row++ ){
		board[row] = new Field_t*[cols];
		for (int col = 0; col < cols; col++){
			(board[row])[col] = new Field_t;
		} 
	}
}

Tetris::~Tetris(){
	for (int row = 0; row < rows; row++){
		for (int col = 0; col < cols; col++){
			delete (board[row])[col];
		}
		delete[] board[row];
	}
	delete[] board;
}

void Tetris::startGame(){
	generateQueue();
	current = *(position++);
	next = *(position++);

}

void Tetris::newTetromino(){
	delete current;
	current = next;
	current->place();
	//this may not work properly
	if (position == queue.end()) generateQueue();
	next = *(position++);
}

void Tetris::generateQueue(){
	Shape* I = new Line;
	Shape* J = new LBend;
	Shape* L = new RBend;
	Shape* S = new LStair;
	Shape* Z = new RStair;
	Shape* T = new MStair;
	Shape* O = new Square;
	std::vector<Shape*> bag = {I, J, L, S, Z, T, O};
	auto bagPos = bag.begin();
	auto queuePos = queue.begin();
	//pick randomized element from bag, and insert into queue
	for (int i = 0; i < 7; i++){
		int rPos = rand() % (7-i);
		*(queuePos++) = *(bagPos + i);
		bag.erase(bagPos + i),
	} 
	position = queue.begin();
}

void Tetris::update(){
	if (height()){
		move(DOWN);
	}else{
		int boardX = current->getPosX();
		int boardY = current->getPosY();

		for (int x = 0; x < current->getWidth(); x++){
			for (int y = 0; y < current->getHeight(); y++){
				Field_t* temp = current->get(x,y);
				if (temp->occupied){
					(*(*(board + boardY + y) + BoardX + x))->occupied = temp->occupied;
					(*(*(board + boardY + y) + BoardX + x))->clr = temp->clr;
				}
			}
		}
		//check for filled rows and remove
		int removeQueue[4] = {-1, -1, -1, -1};
		int index = 0;
		for (int y = 0; y < ROWS; y++){
			if (isRowFull(y)){
				removeQueue[index] = y;
				index++;
			}
		}
		removeRows(removeQueue);
		newTetromino();
	}
}

bool Tetris::isRowFull(int y){
	for (int x = 0; x < COLS; x++ ){
		if (!(*(*(board + y) + x))->occupied)
			return false;
	}
	return true;
}

void Tetris::removeRows(int rowsA[]){
	int startIndex = 3;
	//eliminate non-filled part of array
	while (rowsA[startIndex] == -1) startIndex--;

	int rowsRemoved = 0;
	for (int y = 0; y < ROWS; y++){
		if (startIndex <= 0){
			if (y == rowsA[startIndex]) {
				rowsRemoved++;
				startIndex--;
			}
		}
		if (y + rowsRemoved < ROWS){
			for (int x = 0; x < COLS; x++ ){
				*(*(board + y) + x) = *(*(board + y + rowsRemoved) + x);
			}
		}else{
			for (int x = 0; x < COLS; x++ ){
				(*(*(board + y) + x))->clr = CLEAR;
				(*(*(board + y) + x))->occupied = false;
			}
		} 
	}
}

void Tetris::move(enum Direction dir){
	if (dir == DOWN && height()){
		current->move(DOWN,1);
	}else if (dir == LEFT){
		bool occ = false;
		for (int y = current->getPosY(); y < current->getPosY() + current->getHeight(); y++){
			if (isOccupied(current->getPosX()-1,y)) occ = true;
		}
		if (!occ) current->move(LEFT, 1);
	}else if (dir == RIGHT){

	}
}

void Tetris::rotate(){
	current->rotate();
	if (current->getPosX() + current->getWidth() > COLS){
		int offset = current->getPosX() + current->getWidth() - COLS; 
	}
}

void Tetris::hardDrop(){
	int boardX = current->getPosX();
	int boardY = current->getPosY() - height();
	current->setPos(boardX, boardY);

	// Copy current into board
	for (int x = 0; x < current->getWidth(); x++){
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
* Returns the distance before
* the tetromino will be grounded, 
* in whole fields
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

bool Tetris::isOccupied(int x, int y){
	if (x > -1 && x < COLS && y > -1 && y < ROWS){
		return (*(*(board + y) + x))->occupied;
	}else return true;
}
