#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <new>
#include "shape.h"


Shape::Shape(int c, int r): rows(r),
							cols(c)
{
	space = new Field_t**[rows];
	for (int row = 0; row < rows; row++ )
	{
		*(space + row) = new Field_t*[cols];
		for (int col = 0; col < cols; col++)
			*(*(space + row) + col) = new Field_t;
	}
}

Shape::~Shape(){
	for (int row = 0; row < rows; row++){
		for (int col = 0; col < cols; col++){
			delete *(*(space + row) + col);
		}
		delete[] *(space + row);
	}
	delete[] space;
}

void Shape::set(int col, int row, enum Color tColor, bool occ){
	(*(*(space + row) + col))->clr = tColor;
	(*(*(space + row) + col))->occupied = occ;
}

Field_t* Shape::get(int x, int y){
	if (x >= cols || x < 0 || y < 0 || y >= rows) std::cout << "out of bounds" << std::endl;
	if (*(*(space + y) + x) == nullptr) std::cout << "invalid field" << std::endl;
	//std::cout << "clr = " << (*(*(space + y) + x))->clr << ", occ " << (*(*(space + y) + x))->occupied << std::endl;
	return *(*(space + y) + x);
}

void Shape::rotate(){
	Field_t ***nSpace;
	//set new rows and cols
	std::swap(rows,cols);

	//allocate array for insertion of tile pointers
	nSpace = new Field_t**[rows];
	for (int row = 0; row < rows; row++ ){
		*(nSpace + row) = new Field_t*[cols];
	}
	//move tile pointers to new rotated positions in new array
	for (int row = 0; row < rows; row++){
		for (int col = 0; col < cols; col++){
			std::cout << "For r " << row << ", c " << col << std::endl;
			*(*(nSpace + (rows - row - 1)) + col) = *(*(space + col) + row);
		}
	}
	//delete dynamically allocated array in space (but not the tiles, as they have been transferred)
	for (int col = 0; col < cols; col++){
		delete[] *(space + col);
	}
	delete[] space;
	//set space equal to nSpace pointer before nSpace goes out of scope
	space = nSpace;
}

void Shape::setPos(int x, int y){
	this->xPos = x;
	this->yPos = y;
}

void Shape::move(enum Direction dir, int length){
	if (dir == LEFT){
		xPos -= length;
	}else if (dir == DOWN){
		yPos -= length;
	}else if (dir == RIGHT){
		xPos += length;
	}
}

/****************************************************
* Returns an integer equal to or greater than zero, 
* telling how many empty tiles there are above the ground level
* in the tetromino space in the given column                    
****************************************************/
//Looks like it is no longer in use
////////////////////////////////
int Shape::emptyHeight(int col){
	int y = 0;
	while (!(*(*(space + y) + col))->occupied && y < getHeight()){
		y++;
	}
	return y;
}

int Shape::getHeight(){
	return rows;
}

int Shape::getWidth(){
	return cols;
}

//Get x- and y postitions, respectively
int Shape::getPosX(){
	return xPos;
}

int Shape::getPosY(){
	return yPos;
}

int Shape::emptySpace(int indX){
	int y = 0;
	if (indX >= getWidth()){
		std::cout << "Shape::emptySpace() bug" << std::endl;
	}
	while (!(*(*(space + y) + indX))->occupied && y < getHeight()){
		y++;
	}
	return y;
}

/******************************
* PlEASE NOTE
* if performance problems are experienced when a new tetromino spawns,
* consider removing for loops, and fill in all fields manually to 
* avoid redundant operations
*****************************/

//green shape
LStair::LStair():Shape(2,3){
	//initialize array empty
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	Shape::set(0,2,GREEN,true);
	Shape::set(0,1,GREEN,true);
	Shape::set(1,1,GREEN,true);
	Shape::set(1,0,GREEN,true);	
}

void LStair::place(){
	setPos(4,20);
}

//red shape
RStair::RStair():Shape(2,3){
	//initialize array empty
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	Shape::set(1,2,RED,true);
	Shape::set(1,1,RED,true);
	Shape::set(0,1,RED,true);
	Shape::set(0,0,RED,true);	
}

void RStair::place(){
	setPos(4,20);
}

//purple shape
MStair::MStair():Shape(3,2){
	//initialize array empty
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 2; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	Shape::set(0,0,PURPLE,true);
	Shape::set(1,0,PURPLE,true);
	Shape::set(2,0,PURPLE,true);
	Shape::set(1,1,PURPLE,true);	
}

void MStair::place(){
	setPos(4,20);
}

//yellow shape
Square::Square():Shape(2,2){
	//initialize array filled with yellow
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			Shape::set(x,y,YELLOW,true);
}

void Square::place(){
	setPos(4,20);
}

//blue shape
LBend::LBend():Shape(2,3){
	//initialize array empty
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	Shape::set(0,0,BLUE,true);
	Shape::set(1,0,BLUE,true);
	Shape::set(1,1,BLUE,true);
	Shape::set(1,2,BLUE,true);	
}

void LBend::place(){
	setPos(4,20);
}

//orange shape 
RBend::RBend():Shape(2,3){
	//initialize array empty
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	Shape::set(0,2,ORANGE,true);
	Shape::set(0,1,ORANGE,true);
	Shape::set(0,0,ORANGE,true);
	Shape::set(1,0,ORANGE,true);	
}

void RBend::place(){
	setPos(4,20);
}

//cyan shape
Line::Line():Shape(1,4){
	//fill in occupied tiles
	Shape::set(0,0,CYAN,true);
	Shape::set(0,1,CYAN,true);
	Shape::set(0,2,CYAN,true);
	Shape::set(0,3,CYAN,true);	
}

void Line::place(){
	setPos(4,20);
}
 