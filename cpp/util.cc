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

template <class T>
void print_vector(vector<T> vec) {
    for (T v: vec) {
        cout << v << ' ';
    } puts("");
}

template void print_vector(vector<int> vec);
template void print_vector(vector<float> vec);

template <class T>
void matrix_mul(Array<T> & a, Array<T> & b, Array<T> & d) {
    if (a.shape.size() != 2) {
        puts("matrix_mul: argument a is not matrix"); return;
    }
    if (b.shape.size() != 2) {
        puts("matrix_mul: argument b is not matrix"); return;
    }
    if (a.shape[1] != b.shape[0]) {
        puts("matrix_mul: invalid shape of (a, b)"); return;
    }
    if (a.shape[0] != d.shape[0] || b.shape[1] != d.shape[1]) {
        puts("matrix_mul: invalid shape of d"); return;
    }
    for (int i = 0; i < d.shape[0]; i++) {
        for (int j = 0; j < d.shape[1]; j++) {
            T tmp = 0;
            for (int k = 0; k < a.shape[1]; k++) {
                tmp += a.Get({i, k}) * b.Get({k, j});
            }
            d.Set({i, j}, tmp);
        }
    }
}

template void matrix_mul(Array<int> & a, Array<int> & b, Array<int> & d);
template void matrix_mul(Array<float> & a, Array<float> & b, Array<float> & d)
