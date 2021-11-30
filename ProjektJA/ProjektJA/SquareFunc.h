#pragma once
#include <iostream>

class SquareFunc
{
public:

	//Entering data
	double a;
	double b;
	double c;

	//Calculations
	bool isSquare=0; //is function square (a!=0)
	bool isU=0; //Shape of the function
	double delta=0;
	double deltaroot=0;
	double p=0;
	double q=0; //the pinnacle of the function
	double x1=0; //if exists 
	double x2=0; //if exists (delta>=0)

	SquareFunc(double A, double B, double C): a(A),b(B),c(C){}

	void Check_if_Square_and_U();
};
