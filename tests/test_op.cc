/*
 * Test for operations
 */

#include "graph.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace miniflow;

template <class T> void print_2d_array(Array<T> & arr);

template<>
void print_2d_array<int>(Array<int> & arr) {
    for (int i = 0; i < arr.shape[0]; i++) {
        for (int j = 0; j < arr.shape[1]; j++) {
            printf("%2d ", arr.Get({i, j}));
        } puts("");
    }
}

template<>
void print_2d_array<float>(Array<float> & arr) {
    for (int i = 0; i < arr.shape[0]; i++) {
        for (int j = 0; j < arr.shape[1]; j++) {
            printf("%2.0f ", arr.Get({i, j}));
        } puts("");
    }
}

int main(int argc, char** argv)
{
    srand(time(0));

    Array<float> a({3, 3});
    Array<float> b({3, 3});
    Array<float> c({3, 3});

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a.Set({i, j}, rand() % 100);
            b.Set({i, j}, rand() % 100);
        }
    }

    a.MultiplyTo(b, &c);

    bool error = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (c.Get({i, j}) != a.Get({i, j}) * b.Get({i, j})) {
                printf("Incorrect in (%d, %d)\n", i, j);
                error = true;
                break;
            }
        }
        if (error) break;
    }
    if (error) {
        puts("a:");
        print_2d_array(a);
        puts("b:");
        print_2d_array(b);
        puts("c:");
        print_2d_array(c);
    } else {
        puts("Multiply Successful");
    }
}
