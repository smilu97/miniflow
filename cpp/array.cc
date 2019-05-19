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
Array<ItemType>::Array(const vector<int> _shape, bool alloc) {
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
int Array<ItemType>::GetOffset(const vector<int> indices) const {
    int offset = 0;
    for (int i = 0; i < ndims; i++) {
        offset += strides[i] * indices[i];
    }
    return offset;
}

template <class ItemType>
ItemType Array<ItemType>::Get(const vector<int> indices) const {
    return *((ItemType*)(data + GetOffset(indices)));
}

template <class ItemType>
void Array<ItemType>::Set(const vector<int> indices, const ItemType item) {
    *((ItemType*)(data + GetOffset(indices))) = item;
}

template <class ItemType>
Array<ItemType>* Array<ItemType>::Clone() const {
    Array<ItemType> * res = Array<ItemType>::empty(this->shape);
    memcpy(res->data, this->data, this->nbytes);
    return res;
}

template <class ItemType>
Array<ItemType> Array<ItemType>::BroadcastTo(const vector<int> _shape) const {
    vector<int> strides(_shape.size());
    int diff_sz = _shape.size() - this->shape.size();
    for (int i = 0; i < diff_sz; i++) {
        strides[i] = 0;
    }
    for (int i = diff_sz, j = 0; i < _shape.size(); i++, j++) {
        if (this->shape[j] != _shape[i]) {
            if (this->shape[j] == 1) {
                strides[i] = 0;
            } else {
                puts("BroadcastTo Error");
            }
        } else {
            strides[i] = this->strides[j];
        }
    }
    Array<ItemType> res = *this;
    res.ndims = _shape.size();
    res.shape = _shape;
    res.strides = strides;
    res.alloc = false;
    return res;
}

template <class ItemType>
vector<int> Array<ItemType>::CombineShape(const vector<int> shape_a, const vector<int> shape_b) {
    if (shape_a.size() > shape_b.size()) {
        return Array<ItemType>::CombineShape(shape_b, shape_a);
    }
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
Array<ItemType>* Array<ItemType>::empty(const vector<int> shape) {
    Array<ItemType> * res = new Array<ItemType>(shape);
    return res;
}

template <class ItemType>
Array<ItemType>* Array<ItemType>::zeros(const vector<int> shape) {
    Array<ItemType> * res = new Array<ItemType>(shape);
    memset(res->data, 0, res->nbytes);
    return res;
}

template <class ItemType>
Array<ItemType>* Array<ItemType>::ones(const vector<int> shape) {
    Array<ItemType> * res = new Array<ItemType>(shape);
    ItemType * it = (ItemType*) res->data;
    for (int i = 0; i < res->size; i++) {
        *it++ = 1;
    }
    return res;
}

template <class I, typename F>
void calc_recursive(int level, const Array<I>& a, const Array<I>& b, Array<I> * d, F op) {
    static char *ap, *bp, *dp;
    if (level == -1) {
        ap = a.data;
        bp = b.data;
        dp = d->data;
        calc_recursive(0, a, b, d, op);
        return;
    }
    if (level == a.shape.size()) {
        *((I*)dp) = op((*(I*)ap), *((I*)bp));
        return;
    }
    for (int i = 0; i < a.shape[level]; i++) {
        calc_recursive(level + 1, a, b, d, op);
        ap += a.strides[level];
        bp += b.strides[level];
        dp += d->strides[level];
    }
    ap -= a.strides[level] * a.shape[level];
    bp -= b.strides[level] * a.shape[level];
    dp -= d->strides[level] * a.shape[level];
}

template <class ItemType>
void Array<ItemType>::MultiplyTo(const Array<ItemType> & b, Array<ItemType> * dest) const {
    if (this->shape != b.shape) {
        puts("MultiplyTo(Array): shape (a, b) dismatching error");
    }
    if (this->shape != dest->shape) {
        puts("MultiplyTo(Array): shape (a, dest) dismatching error");
    }
    calc_recursive(-1, *this, b, dest, [](ItemType a, ItemType b) {
        return a * b;
    });
}

template <class ItemType>
void Array<ItemType>::MultiplyTo(float b, Array<ItemType> * dest) const {
    if (this->shape != dest->shape) {
        puts("MultiplyTo(float): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_d = (ItemType*) dest->data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] * b;
    }
}

template <class ItemType>
void Array<ItemType>::MultiplyTo(int b, Array<ItemType> * dest) const {
    if (this->shape != dest->shape) {
        puts("MultiplyTo(int): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_d = (ItemType*) dest->data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] * b;
    }
}

template <class ItemType>
void Array<ItemType>::AddTo(const Array<ItemType>& b, Array<ItemType> * dest) const {
    if (this->shape != b.shape) {
        puts("AddTo(Array): shape (a, b) dismatching error");
    }
    if (this->shape != dest->shape) {
        puts("AddTo(Array): shape (a, dest) dismatching error");
    }
    calc_recursive(-1, *this, b, dest, [](ItemType a, ItemType b) {
        return a + b;
    });
}

template <class ItemType>
void Array<ItemType>::AddTo(float b, Array<ItemType> * dest) const {
    if (this->shape != dest->shape) {
        puts("AddTo(float): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_d = (ItemType*) dest->data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] + b;
    }
}

template <class ItemType>
void Array<ItemType>::AddTo(int b, Array<ItemType> * dest) const {
    if (this->shape != dest->shape) {
        puts("AddTo(int): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_d = (ItemType*) dest->data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] + b;
    }
}

template <class ItemType>
void Array<ItemType>::DivideTo(const Array<ItemType>& b, Array<ItemType> * dest) const {
    if (this->shape != b.shape) {
        puts("DivideTo(Array): shape (a, b) dismatching error");
    }
    if (this->shape != dest->shape) {
        puts("DivideTo(Array): shape (a, dest) dismatching error");
    }
    calc_recursive(-1, *this, b, dest, [](ItemType a, ItemType b) {
        return a / b;
    });
}

template <class ItemType>
void Array<ItemType>::DivideTo(float b, Array<ItemType> * dest) const {
    if (this->shape != dest->shape) {
        puts("DivideTo(float): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_d = (ItemType*) dest->data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] / b;
    }
}

template <class ItemType>
void Array<ItemType>::DivideTo(int b, Array<ItemType> * dest) const {
    if (this->shape != dest->shape) {
        puts("DivideTo(int): shape (a, dest) dismatching error");
    }
    ItemType * arr_a = (ItemType*) this->data;
    ItemType * arr_d = (ItemType*) dest->data;
    for (int i = 0; i < this->size; i++) {
        arr_d[i] = arr_a[i] / b;
    }
}

namespace miniflow {
    template class Array<int>;
    template class Array<float>;
}
