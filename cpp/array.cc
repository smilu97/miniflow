/*
 * array.cc
 * author: smilu97
 */

#include "array.h"
#include "util.h"
#include <cstdlib>
#include <cstring>
using namespace std;
using namespace miniflow;

template <class ItemType>
Array<ItemType>::Array(vector<int> _shape, bool alloc) {
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

    if (alloc) data = (char*) malloc(nbytes);
    this->alloc = alloc;
}

template <class ItemType>
Array<ItemType>::~Array() {
    if (alloc) free(data);
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
Array<ItemType>* Array<ItemType>::Clone() {
    Array<ItemType> * res = Array<ItemType>::empty(this->shape);
    memcpy(res->data, this->data, this->nbytes);
    return res;
}

template <class ItemType>
Array<ItemType> Array<ItemType>::BroadcastTo(vector<int> shape) {
    vector<int> strides(shape.size());
    int diff_sz = shape.size() - this->shape.size();
    for (int i = 0; i < diff_sz; i++) {
        strides[i] = 0;
    }
    for (int i = diff_sz, j = 0; i < shape.size(); i++, j++) {
        if (this->shape[j] != shape[i]) {
            if (this->shape[j] == 1) {
                strides[i] = 0;
            } else {
                puts("BroadcastTo Error");
            }
        } else {
            strides[i] = this->strides[j];
        }
    }
    Array<ItemType> res(shape, false);
    res.strides = strides;
    return res;
}

template <class ItemType>
vector<int> Array<ItemType>::CombineShape(vector<int> shape_a, vector<int> shape_b) {
    if (shape_a.size() > shape_b.size()) swap(shape_a, shape_b);
    vector<int> res(shape_b.size());
    int diff_sz = shape_b.size() - shape_a.size();
    for (int i = 0; i < diff_sz; i++) {
        res[i] = shape_b[i];
    }
    for (int i = 0, j = diff_sz; j < shape_b.size(); i++, j++) {
        int sa = shape_a[i];
        int sb = shape_b[j];
        if (sa != sb) {
            if (sa != 1 && sb != 1) {
                puts("CombineShape Error");
            }
        }
        res[j] = max2(sa, sb);
    }
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

template <class ItemType>
void Array<ItemType>::MultiplyTo(Array<ItemType>& b, Array<ItemType>& dest) {
    if (this->shape != b.shape) {
        puts("MultiplyTo(Array): shape (a, b) dismatching error");
    }
    if (this->shape != dest.shape) {
        puts("MultiplyTo(Array): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_b = (ItemType*) b.data;
    ItemType * arr_d = (ItemType*) dest.data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] * arr_b[i];
    }
}

template <class ItemType>
void Array<ItemType>::MultiplyTo(float b, Array<ItemType>& dest) {
    if (this->shape != dest.shape) {
        puts("MultiplyTo(float): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_d = (ItemType*) dest.data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] * b;
    }
}

template <class ItemType>
void Array<ItemType>::MultiplyTo(int b, Array<ItemType>& dest) {
    if (this->shape != dest.shape) {
        puts("MultiplyTo(int): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_d = (ItemType*) dest.data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] * b;
    }
}

// TODO:
//     void Array<ItemType>::AddTo(Array<ItemType>& b, Array<ItemType>& dest);
//     void Array<ItemType>::AddTo(float b, Array<ItemType>& dest);
//     void Array<ItemType>::AddTo(int b, Array<ItemType>& dest);

//     void Array<ItemType>::DivideTo(Array<ItemType>& b, Array<ItemType>& dest);
//     void Array<ItemType>::DivideTo(float b, Array<ItemType>& dest);
//     void Array<ItemType>::DivideTo(int b, Array<ItemType>& dest);

namespace miniflow {
    template class Array<int>;
    template class Array<float>;
}
