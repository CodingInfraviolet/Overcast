#include "stdafx.h"

double PI = acos(-1.0);
double halfPI = acos(-1.0) / 2.0;

float PIf = (float)acos(-1.0);
float halfPIf = (float)(acos(-1.0) / 2.0);

float toDegrees(float x) { return (x * 180.0f / PIf); }
float toRadians(float x) { return (x * PIf / 180.0f); }