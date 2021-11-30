#include "pch.h"
#include "dllcpp.h"


double count_delta(double a, double b, double c)
{
	double delta = (b * b) - (4 * a * c);
	return delta;
}

double count_deltaroot(double delta)
{
	double deltaroot = sqrt(delta);
	return deltaroot;
}

double count_p(double a, double b)
{
	double p = (0 - (b / (2 * a)));
	return p;
}

double count_q(double a, double delta)
{
	double q = ( - (delta / (4 * a)));
	return q;
}

double count_x1(double a, double b, double deltaroot)
{
	double x1 = ((-b - deltaroot) / (2 * a));
	return x1;
}

double count_x2(double a, double b, double deltaroot)
{
	double x2 = ((-b + deltaroot) / (2 * a));
	return x2;
}