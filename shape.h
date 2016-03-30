#pragma once

enum Color {RED = 0, BLUE = 1, CYAN = 2, YELLOW = 3, GREEN = 4, PURPLE = 5, ORANGE = 6, CLEAR = 7};
enum Direction {LEFT, RIGHT, DOWN};

typedef struct Field{
	enum Color clr;
	bool occupied;
}Field_t;


class Shape{
private:
	int rows;
	int cols;
	Field_t*** space;
	int x, y;
public:
	Shape(int c, int r);
	~Shape();
	void set(int col, int row, enum Color tColor, bool occ);
	Field_t* get(int x, int y);	
	void rotate();
	void setPos(int x, int y);
	void move(Direction dir, int length);
	int emptyHeight(int col);
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();
	int emptySpace(int indX);
	virtual void place() = 0;

};

//green shape
class LStair: public Shape{
public:
	LStair();
	virtual void place();
};

//red shape
class RStair: public Shape{
public:
	RStair();
	virtual void place();
};

//purple shape
class MStair: public Shape{
public:
	MStair();
	virtual void place();
};

//yellow shape
class Square: public Shape{
public:
	Square();
	virtual void place();
};

//blue shape
class LBend: public Shape{
public:
	LBend();
	virtual void place();
};

//orange shape 
class RBend: public Shape{
public:
	RBend();
	virtual void place();
};

//cyan shape
class Line: public Shape{
public:
	Line();
	virtual void place();
};

