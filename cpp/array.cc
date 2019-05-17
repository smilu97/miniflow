/*
 * array.cc
 * author: smilu97
 */

#include "array.h"
#include <cstdlib>
using namespace std;
using namespace miniflow;

template <typename ItemType>
Array<ItemType>::Array(vector<int> _shape) {
    shape = _shape;
    ndims = shape.size();
    itemsize = sizeof(ItemType);
    
    size = 1;
    for (int i = 0; i < ndims; i++) {
        size *= shape[i];
    }
    nbytes = size * sizeof(ItemType);

    int stride = nbytes;
    strides.reserve(ndims);
    for (int i = 0; i < ndims; i++) {
        stride /= shape[i];
        strides.push_back(stride);
    }

    data = (char*) malloc(nbytes);
}

template <typename ItemType>
Array<ItemType>::~Array() {
    free(data);
}

template <typename ItemType>
int Array<ItemType>::GetOffset(vector<int> indices) {
    int offset = 0;
    for (int i = 0; i < ndims; i++) {
        offset += strides[i] * indices[i];
    }
    return offset;
}

template <typename ItemType>
ItemType Array<ItemType>::Get(vector<int> indices) {
    return *((ItemType*)(data + GetOffset(indices)));
}

template <typename ItemType>
void Array<ItemType>::Set(vector<int> indices, ItemType item) {
    *((ItemType*)(data + GetOffset(indices))) = item;
}

namespace miniflow {
    template class Array<int>;
    template class Array<float>;
}
