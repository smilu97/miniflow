/*
 * Graph.cc
 * author: smilu97
 */

#include "graph.h"
using namespace std;
using namespace miniflow;

/*************************
 * class Node
 */

template <class ItemType>
Node<ItemType>::Node() {
    val_ = 0;
}

template <typename ItemType>
Array<ItemType>& Node<ItemType>::GetValue() {
    return *val_;
}

template <typename ItemType>
Node<ItemType>* Node<ItemType>::GetArgument(int index) {
    if (index >= args_.size()) {
        // out bound
        printf("[Runtime Error]: Out of bound: GetArgument(%d)\n", index);
        return 0;
    }
    return args_[index];
}

/*************************
 * class Operation
 */

template <typename ItemType>
Operation<ItemType>::Operation() {
    this->type_ = NT_OP;
}

template <typename ItemType>
Operation<ItemType>::~Operation() {

}

/*************************
 * class Variable
 */

template <typename ItemType>
Variable<ItemType>::Variable(vector<int> shape) {
    this->val_ = new Array<ItemType>(shape);
    this->type_ = NT_VAR;
}

template <typename ItemType>
Variable<ItemType>::~Variable() {

}

template <typename ItemType>
void Variable<ItemType>::SetValue(Array<ItemType> * val) {
    this->val_ = val;
}

/*************************
 * class Placeholder
 */

template <typename ItemType>
Placeholder<ItemType>::Placeholder() {
    this->type_ = NT_PH;
}

template <typename ItemType>
Placeholder<ItemType>::~Placeholder() {
    
}

namespace miniflow {
    template class Node<int>;
    template class Node<float>;
    template class Placeholder<int>;
    template class Placeholder<float>;
    template class Variable<int>;
    template class Variable<float>;
}

