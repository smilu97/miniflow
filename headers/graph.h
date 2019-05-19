/*
 * Graph.h
 * author: smilu97
 */
#pragma once

#include "array.h"
#include <vector>
using namespace std;

namespace miniflow {

	enum NodeType {
		NT_OP = 0,
		NT_VAR,
		NT_PH,
	};

	class Node {
	protected:
		NodeType type_;
		vector<Node*> args_;
		void * val_;
	public:
		Node();
		Node* GetArgument(int index);

		void SetInt(int val);
		void SetFloat(float val);
		template <class ItemType>
		void SetArray(Array<ItemType> val);
		
		int GetInt();
		float GetFloat();
		template <class ItemType>
		Array<ItemType> GetArray();
	};

	class Operation: public Node {
	public:
		virtual void Update() = 0;
		Operation();
		~Operation();
	};

	template <class ValueType>
	class Variable: public Node {
	public:
		Variable();
		~Variable();
		void SetValue(ValueType val);
	};

	template <class ValueType>
	class Placeholder: public Node {
	public:
		Placeholder();
		~Placeholder();
	};

}
