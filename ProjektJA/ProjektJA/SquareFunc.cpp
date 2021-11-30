#include "SquareFunc.h"

void SquareFunc::Check_if_Square_and_U()
{
	if (a != 0)
	{
		isSquare = true;
		if (a > 0)
			isU = true;
		else
			isU = false;
	}
	else
	{
		isSquare = false;
		if (a > 0)
			isU = true;
		else
			isU = false;
	}
}