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
        int GetOffset(const vector<int> & indices) const;
        ItemType Get(const vector<int> & _indices) const;
        void Set(const vector<int> & indices, const ItemType item);
        Array<ItemType>* Clone() const;
        
        Array<ItemType> BroadcastTo(const vector<int> & shape) const;
        static vector<int> CombineShape(
            const vector<int> & shape_a,
            const vector<int> & shape_b
        );

        static Array<ItemType>* empty(const vector<int> & shape);
        static Array<ItemType>* zeros(const vector<int> & shape);
        static Array<ItemType>* ones(const vector<int> & shape);

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
