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

Node::Node() {
    val_ = 0;
}

Node* Node::GetArgument(int index) const {
    if (index >= args_.size()) {
        // out bound
        printf("[Runtime Error]: Out of bound: GetArgument(%d)\n", index);
        return 0;
    }
    return args_[index];
}

void Node::SetInt(int val) {
    this->val_ = new int(val);
}

void Node::SetFloat(float val) {
    this->val_ = new float(val);
}

template <class ItemType>
void Node::SetArray(const Array<ItemType> val) {
    this->val_ = val.Copy();
}

int Node::GetInt() const {
    return *((int*) this->val_);
}

float Node::GetFloat() const {
    return *((float*) this->val_);
}

template <class ItemType>
Array<ItemType>* Node::GetArray() const {
    return (Array<ItemType>*) this->val_;
}

/*************************
 * class Operator
 */

Operator::Operator() {
    this->type_ = NT_OP;
}

Operator::~Operator() {

}

/*************************
 * class Variable
 */

template <class ValueType>
Variable<ValueType>::Variable() {
    this->val_ = new ValueType;
    this->type_ = NT_VAR;
}

template <class ValueType>
Variable<ValueType>::~Variable() {

}

template <class ValueType>
void Variable<ValueType>::SetValue(const ValueType val) {
    this->val_ = new ValueType(val);
}

/*************************
 * class Placeholder
 */

template <class ValueType>
Placeholder<ValueType>::Placeholder() {
    this->type_ = NT_PH;
}

template <class ValueType>
Placeholder<ValueType>::~Placeholder() {
    
}

namespace miniflow {
    template Array<int>* Node::GetArray() const;
    template Array<float>* Node::GetArray() const;
}

