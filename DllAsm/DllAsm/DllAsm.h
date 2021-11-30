#pragma once
#include <windows.h>
#ifdef DLLASM_EXPORTS
#define DLLASM_API __declspec(dllexport)
#else
#define DLLASM_API __declspec(dllimport)
#endif
extern "C" DLLASM_API double count_delta(double,double,double);
extern "C" DLLASM_API double count_deltaroot(double);
extern "C" DLLASM_API double count_p(double,double);
extern "C" DLLASM_API double count_q(double,double);
extern "C" DLLASM_API double count_x1(double,double,double);
extern "C" DLLASM_API double count_x2(double,double,double);