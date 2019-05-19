/*
 * Test for broadcasting
 */

#include "graph.h"
#include "util.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace miniflow;

void print_2d_array(Array<int> & arr) {
    for (int i = 0; i < arr.shape[0]; i++) {
        for (int j = 0; j < arr.shape[1]; j++) {
            printf("%2d ", arr.Get({i, j}));
        } puts("");
    }
}

int main(int argc, char** argv)
{
    srand(time(0));

    Array<int> a({3});
    Array<int> b({3, 1});

    for (int i = 0; i < 3; i++) {
        a.Set({i}, rand() % 100);
        b.Set({i, 0}, rand() % 100);
    }
    
    vector<int> shape_res = Array<int>::CombineShape(a.shape, b.shape);
    // printf("shape_res: "); print_vector(shape_res);

    Array<int> C(shape_res);

    Array<int> A = a.BroadcastTo(shape_res);
    Array<int> B = b.BroadcastTo(shape_res);

    // puts("A:"); print_2d_array(A);
    // puts("B:"); print_2d_array(B);

    // printf("a: %d %d %d\n", a.Get({0}), a.Get({1}), a.Get({2}));
    // printf("A.strides: "); print_vector(A.strides);
    // printf("A.shape: "); print_vector(A.shape);

    // printf("a: %p\n", a.data);
    // printf("b: %p\n", b.data);
    // printf("C: %p\n", C.data);
    // printf("A: %p\n", A.data);
    // printf("B: %p\n", B.data);

    A.MultiplyTo(B, &C);

    // puts("C:"); print_2d_array(C);

    bool error = false;
    for (int i = 0; i < shape_res[0]; i++) {
        for (int j = 0; j < shape_res[1]; j++) {
            if (C.Get({i, j}) != a.Get({j}) * b.Get({i, 0})) {
                error = true;
                printf("Incorrection in (%d, %d)\n", i, j);
                break;
            }
        }
        if (error) break;
    }
    if (error) {
        puts("Broadcasting test failed!");
    } else {
        puts("Broadcasting test successful!");
    }
}
