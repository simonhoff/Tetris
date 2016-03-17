#include <cstdlib>
#include <new>
#include "shape.h"


Shape(int c, int r):rows(r),
					cols(c)
{
	space = new Tile_t**[rows];
	for (int row = 0; row < rows; row++ )
	{
		*(space + row) = new Tile_t*[cols];
		for (int col = 0; col < cols; col++)
			*(*(space + row) + col) = new Tile_t;
	}
}

Shape::~Shape(){
	for (int row = 0; row < nRows; row++){
		for (int col = 0; col < nCols; col++){
			delete *(*(space + row) + col);
		}
		delete[] *(space + row);
	}
	delete[] space;
}

void set(int col, int row, enum Color tColor, bool occ){
	(*(*(space + row) + col))->clr = tColor;
	(*(*(space + row) + col))->occupied = occ;
}

void Shape::rotate(){
	Tile_t ***nSpace;
	//set new rows and cols
	std::swap(rows,cols);

	//allocate array for insertion of tile pointers
	nSpace = new Tile_t**[rows];
	for (int row = 0; row < rows; row++ )
		*(nSpace + row) = new Tile_t*[cols];

	//move tile pointers to new rotated positions in new array
	for (int row = 0; row < rows; row++){
		for (int col = 0; col < cols; col++){
			*(*(nSpace + (cols - col)) + row) = *(*(space + row) + col);
		}
	}
	//delete dynamically allocated array in space (but not the tiles, as they have been transferred)
	for (int row = 0; row < nRows; row++){
		delete[] *(space + row);
	}
	delete[] space;
	//set space equal to nSpace pointer before nSpace goes out of scope
	space = nSpace;
}

/******************************
* PlEASE NOTE
* if performance problems are experienced when a new tetromino spawns,
* consider removing for loops, and fill in all fields manually to 
* avoid redundant operations
*****************************/

//green shape
LStair::LStair():Shape::Shape(2,3){
	//initialize array empty
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	set(0,2,GREEN,true);
	set(0,1,GREEN,true);
	set(1,1,GREEN,true);
	set(1,0,GREEN,true);	
}

//red shape
RStair::RStair():Shape::Shape(2,3){
	//initialize array empty
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	set(2,2,RED,true);
	set(2,1,RED,true);
	set(1,1,RED,true);
	set(1,0,RED,true);	
}

//purple shape
MStair::MStair():Shape::Shape(3,2){
	//initialize array empty
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 2; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	set(0,0,PURPLE,true);
	set(1,0,PURPLE,true);
	set(2,0,PURPLE,true);
	set(1,1,PURPLE,true);	
}

//yellow shape
Square::Square():Shape::Shape(2,2){
	//initialize array filled with yellow
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,YELLOW,true);
}

//blue shape
LBend::LBend():Shape::Shape(2,3){
	//initialize array empty
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	set(0,0,BLUE,true);
	set(1,0,BLUE,true);
	set(1,1,BLUE,true);
	set(1,2,BLUE,true);	
}

//orange shape 
RBend::RBend():Shape::Shape(2,3){
	//initialize array empty
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	set(0,2,ORANGE,true);
	set(0,1,ORANGE,true);
	set(0,0,ORANGE,true);
	set(1,0,ORANGE,true);	
}

//cyan shape
Line::Line():Shape::Shape(){
	//initialize array empty
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			set(x,y,CLEAR,false);
	//fill in occupied tiles
	set(2,2,CYAN,true);
	set(2,1,CYAN,true);
	set(1,1,CYAN,true);
	set(1,0,CYAN,true);	
}
 