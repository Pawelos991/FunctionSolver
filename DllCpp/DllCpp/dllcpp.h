#pragma once
#include <math.h>

#ifdef DLLCPP_EXPORTS
#define DLLCPP_API __declspec(dllexport)
#else
#define DLLCPP_API __declspec(dllimport)
#endif
extern "C" DLLCPP_API double count_delta(double a, double b, double c);
extern "C" DLLCPP_API double count_deltaroot(double delta);
extern "C" DLLCPP_API double count_p(double a, double b);
extern "C" DLLCPP_API double count_q(double a, double delta);
extern "C" DLLCPP_API double count_x1(double a, double b, double deltaroot);
extern "C" DLLCPP_API double count_x2(double a, double b, double deltaroot);
