/*
 * Utility functions
 */
#pragma once

#include "array.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace miniflow;

template <class T>
T max2(T a, T b);

template <class T>
T min2(T a, T b);

template <class T>
void print_vector(vector<T> vec);

template <class T>
void matrix_mul(const Array<T> & a, const Array<T> & b, Array<T> * d);
