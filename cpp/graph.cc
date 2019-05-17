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

Node* Node::GetArgument(int index) {
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
void Node::SetArray(Array<ItemType> val) {
    this->val_ = val.Copy();
}

int Node::GetInt() {
    return *((int*) this->val_);
}

float Node::GetFloat() {
    return *((float*) this->val_);
}

template <class ItemType>
Array<ItemType> Node::GetArray() {
    return (Array<ItemType>*) this->val_;
}

/*************************
 * class Operation
 */

Operation::Operation() {
    this->type_ = NT_OP;
}

Operation::~Operation() {

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
void Variable<ValueType>::SetValue(ValueType val) {
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
    
}

