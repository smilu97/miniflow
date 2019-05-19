/*
 * basic operators
 * author: smilu97
 */
#pragma once

#include "array.h"
#include "graph.h"
using namespace std;

namespace miniflow {

template <class ItemType>
class AddOp: public Operator {
    void Update();
};

template <class ItemType>
class AddOp<Array<ItemType>>: public Operator {
    void Update();
};

template <class ItemType>
class SubOp: public Operator {
    void Update();
};

template <class ItemType>
class MulOp: public Operator {
    void Update();
};

}
