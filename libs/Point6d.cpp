//Developed by Davide Valeriani
//www.davidevaleriani.it

#include "Point6d.h"

Point6d::Point6d(void) {
	x = 0;
	y = 0;
	z = 0;
	a = 0;
	b = 0;
	c = 0;
}

Point6d::Point6d(double x1, double y1, double z1, double a1, double b1, double c1){
	x = x1;
	y = y1;
	z = z1;
	a = a1;
	b = b1;
	c = c1;
}

Point6d::~Point6d(void)
{
}

double Point6d::getX(void) {
	return x;
}

double Point6d::getY(void) {
	return y;
}

double Point6d::getZ(void) {
	return z;
}

double Point6d::getA(void) {
	return a;
}

double Point6d::getB(void) {
	return b;
}

double Point6d::getC(void) {
	return c;
}

void Point6d::setX(double t) {
	x = t;
}

void Point6d::setY(double t) {
	y = t;
}

void Point6d::setZ(double t) {
	z = t;
}

void Point6d::setA(double t) {
	a = t;
}

void Point6d::setB(double t) {
	b = t;
}

void Point6d::setC(double t) {
	c = t;
}

bool operator == ( Point6d & p1,  Point6d & p2) {
    return ((p1.getX () == p2.getX ()) && (p1.getY () == p2.getY ()) && (p1.getZ () == p2.getZ ()) &&
        (p1.getA () == p2.getA ()) && (p1.getB () == p2.getB ()) && (p1.getC () == p2.getC ()));
}

std::ostream& operator <<(std::ostream& out, Point6d& p1) {
    out<<p1.getX()<<"\t"<<p1.getY()<<"\t"<<p1.getZ()<<"\t"<<p1.getA()<<"\t"<<p1.getB()<<"\t"<<p1.getC()<<std::endl;
    return out;
}