/*
 * array.cc
 * author: smilu97
 */

#include "array.h"
#include <cstdlib>
#include <cstring>
using namespace std;
using namespace miniflow;

template <class ItemType>
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

template <class ItemType>
Array<ItemType>::~Array() {
    free(data);
}

template <class ItemType>
int Array<ItemType>::GetOffset(vector<int> indices) {
    int offset = 0;
    for (int i = 0; i < ndims; i++) {
        offset += strides[i] * indices[i];
    }
    return offset;
}

template <class ItemType>
ItemType Array<ItemType>::Get(vector<int> indices) {
    return *((ItemType*)(data + GetOffset(indices)));
}

template <class ItemType>
void Array<ItemType>::Set(vector<int> indices, ItemType item) {
    *((ItemType*)(data + GetOffset(indices))) = item;
}

template <class ItemType>
Array<ItemType>* Array<ItemType>::Copy() {
    Array<ItemType> * res = Array<ItemType>.empty(this->shape);
    memcpy(res->data, this->data, this->nbytes);
    return res;
}

template <class ItemType>
Array<ItemType>* Array<ItemType>::empty(vector<int> shape) {
    Array<ItemType> * res = new Array<ItemType>(shape);
    return res;
}

template <class ItemType>
Array<ItemType>* Array<ItemType>::zeros(vector<int> shape) {
    Array<ItemType> * res = new Array<ItemType>(shape);
    memset(res->data, 0, res->nbytes);
    return res;
}

template <class ItemType>
Array<ItemType>* Array<ItemType>::ones(vector<int> shape) {
    Array<ItemType> * res = new Array<ItemType>(shape);
    ItemType * it = (ItemType*) res->data;
    for (int i = 0; i < res->size; i++) {
        *it++ = 1;
    }
    return res;
}

namespace miniflow {
    template class Array<int>;
    template class Array<float>;
}
