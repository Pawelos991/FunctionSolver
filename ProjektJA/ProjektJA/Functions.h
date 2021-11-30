#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <windows.h>

#include "SquareFunc.h"


typedef double(CALLBACK* LPFNDLLFUNC)(double);
typedef double(CALLBACK* LPFNDLLFUNC2)(double,double);
typedef double(CALLBACK* LPFNDLLFUNC3)(double,double,double);

void LoadFromFile(std::vector<SquareFunc>& Funcs);

void SaveResultsToFile(bool cpp, std::vector<SquareFunc>& Funcs);


