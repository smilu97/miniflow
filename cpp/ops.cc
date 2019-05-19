/*
 * basic operators
 * author: smilu97
 */

#include "ops.h"
using namespace std;
using namespace miniflow;

template <>
void AddOp<int>::Update() {
    int a = this->GetArgument(0)->GetInt();
    int b = this->GetArgument(1)->GetInt();
    this->SetInt(a + b);
}

template <>
void AddOp<float>::Update() {
    float a = this->GetArgument(0)->GetFloat();
    float b = this->GetArgument(1)->GetFloat();
    this->SetFloat(a + b);
}

template<>
void AddOp<Array<int>>::Update() {
    Array<int> * a = this->GetArgument(0)->GetArray<int>();
    Array<int> * b = this->GetArgument(1)->GetArray<int>();
    Array<int> * d = this->GetArray<int>();

    vector<int> cshape = Array<int>::CombineShape(a->shape, b->shape);
    Array<int> A = a->BroadcastTo(cshape);
    Array<int> B = b->BroadcastTo(cshape);
    A.AddTo(B, d);
}

template <>
void SubOp<int>::Update() {
    int a = this->GetArgument(0)->GetInt();
    int b = this->GetArgument(1)->GetInt();
    this->SetInt(a - b);
}

template <>
void SubOp<float>::Update() {
    float a = this->GetArgument(0)->GetFloat();
    float b = this->GetArgument(1)->GetFloat();
    this->SetFloat(a - b);
}

template <>
void MulOp<int>::Update() {
    int a = this->GetArgument(0)->GetInt();
    int b = this->GetArgument(1)->GetInt();
    this->SetInt(a + b);
}

template <>
void MulOp<float>::Update() {
    float a = this->GetArgument(0)->GetFloat();
    float b = this->GetArgument(1)->GetFloat();
    this->SetFloat(a + b);
}
