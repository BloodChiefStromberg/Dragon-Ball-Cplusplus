//Point.h: simple point(x, y) class to simplify some stuff, especially testing

#ifndef _Point
#define _Point

class Point
{
public:
	//Constructor
	Point(int iX, int iY);

	//Getters
	int getX();
	int getY();

	//Setters
	void setX(int iX);
	void setY(int iY);
private:
	int m_iX;
	int m_iY;
};

#endif
