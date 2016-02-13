//Developed by Davide Valeriani
//www.davidevaleriani.it

#pragma once

#include <ostream>
class Point6d
{
	 public:
		Point6d(void);
		Point6d(double, double, double, double, double, double);
		~Point6d(void);
		double getX(void);
		double getY(void);
		double getZ(void);
		double getA(void);
		double getB(void);
		double getC(void);
		void setX(double);
		void setY(double);
		void setZ(double);
		void setA(double);
		void setB(double);
		void setC(double);
	 private:
		double x;
		double y;
		double z;
		double a;
		double b;
		double c;
	};

bool operator == (Point6d& p1, Point6d& p2);
std::ostream& operator <<(std::ostream& outputStream, Point6d& p1);