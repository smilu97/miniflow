/*
 * basic operators
 * author: smilu97
 */

#include "ops.h"
using namespace std;
using namespace miniflow;

template <>
void AddOp<Array<float>>::Update() {
    Array<float> * a = this->GetArgument(0)->GetArray<float>();
    Array<float> * b = this->GetArgument(1)->GetArray<float>();
    Array<float> * d = this->GetArray<float>();

    vector<int> cshape = Array<float>::CombineShape(a->shape, b->shape);
    Array<float> A = a->BroadcastTo(cshape);
    Array<float> B = b->BroadcastTo(cshape);
    A.AddTo(B, d);
}

template <>
void SubOp<Array<float>>::Update() {
    Array<float> * a = this->GetArgument(0)->GetArray<float>();
    Array<float> * b = this->GetArgument(1)->GetArray<float>();
    Array<float> * d = this->GetArray<float>();

    vector<int> cshape = Array<float>::CombineShape(a->shape, b->shape);
    Array<float> A = a->BroadcastTo(cshape);
    Array<float> B = b->BroadcastTo(cshape);
    A.SubTo(B, d);
}

template <>
void MulOp<Array<float>>::Update() {
    Array<float> * a = this->GetArgument(0)->GetArray<float>();
    Array<float> * b = this->GetArgument(1)->GetArray<float>();
    Array<float> * d = this->GetArray<float>();

    vector<int> cshape = Array<float>::CombineShape(a->shape, b->shape);
    Array<float> A = a->BroadcastTo(cshape);
    Array<float> B = b->BroadcastTo(cshape);
    A.MultiplyTo(B, d);
}
