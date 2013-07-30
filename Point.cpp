//Point.cpp: implements functions defined in Point.h

#include "Point.h"

//Constructor
Point::Point(int iX, int iY)
{
	m_iX = iX;
	m_iY = iY;
}

//Getters
int Point::getX()
{
	return m_iX;
}

int Point::getY()
{
	return m_iY;
}

//Setters
void Point::setX(int iX)
{
	m_iX = iX;
}

void Point::setY(int iY)
{
	m_iY = iY;
}
