#include <cstdlib>
#include <iostream>
#include <string>
#include <new>
#include <vector>
#include "Tetris.h"
#include "shape.h"

#define ROWS 24
#define COLS 10

Tetris::Tetris(){
	rows = ROWS;
	cols = COLS;
	board = new Field_t**[rows];
	for (int row = 0; row < rows; row++ ){
		board[row] = new Field_t*[cols];
		for (int col = 0; col < cols; col++){
			(board[row])[col] = new Field_t;
			((board[row])[col])->clr = CLEAR;
			((board[row])[col])->occupied = false;
		} 
	}
}

void Tetris::checkBoard(){
	for (int y = 0; y < rows; y++){
		for (int x = 0; x < cols; x++){
			if (!((*(*(board + y) + x))->clr == CLEAR))
				std::cout << "clr fault at x = " << x << " y = " << y << std::endl;
			if ((*(*(board + y) + x))->occupied)
				std::cout << "occ fault at x = " << x << " y = " << y << std::endl;
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
	current = queue[position++];
	current->place();
	next = queue[position++];

}

void Tetris::newTetromino(){
	delete current;
	current = nullptr;
	current = next;
	current->place();
	if (position == 7) 
		generateQueue();
	next = queue[position++];
}

void Tetris::generateQueue(){
	queue.clear();
	Shape* I = new Line;
	Shape* J = new LBend;
	Shape* L = new RBend;
	Shape* S = new LStair;
	Shape* Z = new RStair;
	Shape* T = new MStair;
	Shape* O = new Square;
	std::vector<Shape*> bag = {I, J, L, S, Z, T, O};
	auto bagPos = bag.begin();
	//pick randomized element from bag, and insert into queue
	for (int i = 0; i < 7; i++){
		int rPos = rand() % (7-i);
		queue.push_back( *(bagPos + rPos) );
		bag.erase(bagPos + rPos);
	} 
	position = 0;
}

void Tetris::update(){
	if (height() > 0){
		this->move(DOWN);
	}else{
		std::cout << "Placing tetromino" << std::endl;
		int boardX = current->getPosX();
		int boardY = current->getPosY();
		//Place tetromino
		for (int x = 0; x < current->getWidth(); x++){
			for (int y = 0; y < current->getHeight(); y++){
				Field_t* temp = current->get(x, y);

				if (temp->occupied){
					(*(*(board + boardY + y) + boardX + x))->occupied = true;
					enum Color tmp = temp->clr;
					std::cout << "tmpclr " << tmp << std::endl;
					(*(*(board + boardY + y) + boardX + x))->clr = temp->clr;
				}			
			}
		}
		removeCheck();
		
		newTetromino();
	}
}

void Tetris::removeCheck(){
	//check for filled rows and remove
	bool doRemove = false;
	int removeQueue[4] = {-1, -1, -1, -1};
	int index = 0;
	for (int y = 0; y < ROWS; y++){
		if (isRowFull(y) && index < 4){
			doRemove = true;
			removeQueue[index] = y;
			index++;
			std::cout << "Marking row " << y << " for removal" << std::endl;
		}
	}
	if (doRemove){
		removeRows(removeQueue);
	}
}


bool Tetris::isRowFull(int y){
	for (int x = 0; x < COLS; x++ ){
		if (!isOccupied(x,y))
			return false;
	}
	return true;
}

void Tetris::removeRows(int rowsA[]){
	//int startIndex = 3;
	//eliminate non-filled part of array
	//while (rowsA[startIndex] == -1) startIndex--;
	
	std::cout << "RemoveVector" << std::endl;
	for (int x = 0; x < 4; x++) std::cout << rowsA[x] << ", ";
	std::cout << std::endl;

	int index = 0;
	int rowsRemoved = 0;
	for (int y = 0; y < ROWS; y++){
		if (index < 4){
			if (y == rowsA[index]) {
				rowsRemoved++;
				index++;
			}
		}
		if (y + rowsRemoved < ROWS){
			for (int x = 0; x < COLS; x++ ){
				(*(*(board + y) + x))->clr = (*(*(board + y + rowsRemoved) + x))->clr;
				(*(*(board + y) + x))->occupied = (*(*(board + y + rowsRemoved) + x))->occupied;
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
	//need to add consideration for empty fields inside shape space
	if (dir == DOWN && height()){
		current->move(DOWN,1);
	}else if (dir == LEFT){
		bool occ = false;
		for (int y = current->getPosY(); y < current->getPosY() + current->getHeight(); y++){
			if (isOccupied(current->getPosX()-1,y)) occ = true;
		}
		if (!occ) current->move(LEFT, 1);
	//Needs debug
	}else if (dir == RIGHT){
		bool occ = false;
		for (int y = current->getPosY(); y < current->getPosY() + current->getHeight(); y++){
			if (isOccupied(current->getPosX() + current->getWidth(), y)) occ = true;
		}
		if (!occ) current->move(RIGHT, 1);
	}
}

void Tetris::rotate(){
	current->rotate();
	if (current->getPosX() + current->getWidth() > COLS){
		int offset = current->getPosX() + current->getWidth() - COLS;
		std::cout << "offset " << offset << std::endl;
		current->setPos(current->getPosX() - offset, current->getPosY());
	}

	checkOverlap:
	std::cout << "overlapCheck" << std::endl;
	int boardX = current->getPosX();
	int boardY = current->getPosY();
	//bottom
	for (int x = 0; x < current->getWidth(); x++){
		Field_t* temp = current->get(x,0);
		if (temp->occupied && (*(*(board + boardY) + boardX + x))->occupied){

			goto checkOverlap;
		}
	}
	//sides
	for (int y = 0; y < current->getHeight(); y++){
		Field_t* temp = current->get(0,y);
		if (temp->occupied && (*(*(board + boardY + y) + boardX))->occupied){
			current->setPos(current->getPosX(), current->getPosY() + 1);
			goto checkOverlap;
		}
		temp = current->get(current->getWidth()-1,y);
		if (temp->occupied && (*(*(board + boardY + y) + boardX + current->getWidth() - 1))->occupied){
			current->setPos(current->getPosX(), current->getPosY() + 1);
			goto checkOverlap;
		}
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
	removeCheck();
	newTetromino();
}

/*********************************
* Returns the distance before
* the tetromino will be grounded, 
* in whole fields
*********************************/
int Tetris::height(){
	int counter = 0;
	int pos = current->getPosX();
	int mHeight = ROWS;
	if (current->getWidth() + pos > COLS) std::cout << "height click" << std::endl;
	for (int indX = pos; indX < (pos + current->getWidth()); indX++){
		int h = 0;
		int y = current->getPosY() + current->emptySpace(indX - pos);
		while (!isOccupied(indX, y - 1) && y > 0){
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

Field_t* Tetris::get(int x, int y){
	if (x >= current->getPosX() && x < current->getPosX() + current->getWidth() && 
		y >= current->getPosY() && y < current->getPosY() + current->getHeight())
	{
		Field_t* temp = current->get(x - current->getPosX(), y - current->getPosY());
		if (temp->occupied){
			//std::cout << "returning temp, x = " << x << " y = " << y << std::endl;
			return temp;
		}else{
			return (*(*(board + y) + x));
		}
	}
	else{
		//std::cout << "returning board x = " << x << " y = " << y << std::endl;
		return (*(*(board + y) + x));
	}
}

bool Tetris::isGameLost(){
	for (int x = 0; x < COLS; x++){
		if (isOccupied(x,19))
			return true;
	}
	return false;
}

