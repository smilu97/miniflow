/*
 * array.h
 * author: smilu97
 */
#pragma once

#include <vector>
#include <tuple>
using namespace std;

namespace miniflow {

struct NDarray {
    vector<int> shape;
    vector<int> strides;
    int ndims;
    char * data;
    int size;
    int itemsize;
    int nbytes;
};

template <typename ItemType = float>
class Array: public NDarray {
    bool alloc;
public:

    /*
        * @arguments:
        *   _shape[in]: the shape of new Array
        *   alloc[in]: allocate new chunk for data
        *     this option exists because we might need some array
        *     pointing same memory chunk, but having different
        *     shape or strides.
        *     true:
        *       allocate own new memory chunk for data.
        *       free memory chunk on destruction.
        *     false:
        *       doesn't allocate new memory, but just point NULL.
        *       doesn't free memory chunk on destruction.
        */
    Array(const vector<int> & _shape, bool alloc=true);
    ~Array();

    /*
        * @arguments:
        *   indices[in]: the indices of target item.
        * @description:
        *   calculate the byte offset to the target item.
        */
    int GetOffset(const vector<int> & indices) const;

    /*
        * @arguments:
        *   indices[in]: the indices of target item.
        * @description:
        *   read the value of target item.
        */
    ItemType Get(const vector<int> & _indices) const;

    /*
        * @arguments:
        *   indices[in]: the indices of target item.
        *   item[in]: the value to write
        * @description:
        *   write value to the target item.
        */
    void Set(const vector<int> & indices, const ItemType item);

    /*
        * @description:
        *   make new array having own memory chunk having same value
        *   with this.
        */
    Array<ItemType>* Clone() const;
    
    /*
        * @arguments:
        *   shape[in]: the target shape to broadcast
        * @description:
        *   make new array pointing same memory chunk with this,
        *   but having different shape(in argument), and strides.
        */
    Array<ItemType> BroadcastTo(const vector<int> & shape) const;

    /*
        * @arguments:
        *   shape_a[in]: shape a
        *   shape_b[in]: shape b
        * @description:
        *   find a shape including both shapes in arguments.
        *   ex)
        *     if, a: (2, 1, 3), b: (4, 1, 5, 3)
        *     then, res: (4, 2, 5, 3)
        */
    static vector<int> CombineShape(
        const vector<int> & shape_a,
        const vector<int> & shape_b
    );

    /*
        * @arguments:
        *   shape[in]: the shape of new array
        * @description:
        *   make new array having the shape in arguments.
        *   initialized with the value: junk, 0, 1 depending on
        *   which function was called: empty, zeros, ones.
        */
    static Array<ItemType>* empty(const vector<int> & shape);
    static Array<ItemType>* zeros(const vector<int> & shape);
    static Array<ItemType>* ones(const vector<int> & shape);

    /*
        * @arguments:
        *   b[in]: another operand
        *   dest[out]: the result is saved in this.
        * @description:
        *   multiply all each elements in this, and b[in].
        *   and save them in dest[out].
        */
    void MultiplyTo(
        const Array<ItemType> & b,
        Array<ItemType> * dest
    ) const;
    void MultiplyTo(float b, Array<ItemType> * dest) const;
    void MultiplyTo(int b, Array<ItemType> * dest) const;

    void AddTo(const Array<ItemType> & b, Array<ItemType> * dest) const;
    void AddTo(float b, Array<ItemType> * dest) const;
    void AddTo(int b, Array<ItemType> * dest) const;

    void DivideTo(const Array<ItemType> & b, Array<ItemType> * dest) const;
    void DivideTo(float b, Array<ItemType> * dest) const;
    void DivideTo(int b, Array<ItemType> * dest) const;
};

}
