/*
 * utility functions
 */

#include "util.h"

template <class T>
T max2(T a, T b) { return a < b ? b : a; }

template <class T>
T min2(T a, T b) { return a < b ? a : b; }

template int min2(int a, int b);
template float min2(float a, float b);
template int max2(int a, int b);
template float max2(float a, float b);
