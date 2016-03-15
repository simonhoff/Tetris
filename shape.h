#pragma once

enum Color = {RED, BLUE, CYAN, YELLOW, GREEN, PURPLE, ORANGE, CLEAR};
enum Direction = {LEFT, RIGHT, DOWN};

typedef struct Field{
	enum Color clr;
	bool occupied;
}Field_t;


class Shape{
private:
	int rows;
	int cols;
	Field_t*** space;
public:
	Shape(int c, int r);
	void set(int col, int row, enum Color col, bool occ);
	~Shape();	
	void rotate();
};

//green shape
class LStair: public Shape{
public:
	LStair();
};

//red shape
class RStair: public Shape{
public:
	RStair();
};

//purple shape
class MStair: public Shape{
public:
	MStair();
};

//yellow shape
class Square: public Shape{
public:
	Square();
};

//blue shape
class LBend: public Shape{
public:
	LBend();
};

//orange shape 
class RBend: public Shape{
public:
	RBend();
};

//cyan shape
class Line: public Shape{
public:
	Line();
}